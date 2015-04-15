#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <regex.h> 

#include "preproc.h"
#include "typemod.h"
#include "eicval.h"
#include "global.h"
#include "lexer.h"
#include "link2eic.h"

#define max(x,y) ((x) > (y) ? (x) : (y))

#define ST_IDLE		0
#define ST_UP		1
#define ST_LINKED	2
#define ST_DOWN		3

static int fdin=-1, fdout=-1, fderr=-1;
static int nfds;
static int fsm = ST_IDLE;
static int capability = 0;
static int debug_mode = 0;
static char *volatile_data_file = "volatile.dat";

#define RBUFSIZ	1024
#define TIMEOUT	3
#define MAXARGS	32

/* 500 mS retry delay */
#define RETRY_DELAY 500000

int
send_pipe(char *msg)
{
	int len, n;

	len = strlen(msg);
	/* always successful if debug */
	if(debug_mode) return len;
	assert(msg[len-1] == '\n');
	n = write(fdin, msg, len);
	assert(n == len);
	return n;
}

int
recv_pipe(char *bufp)
{
	int n, ready_stdout;
	fd_set readfds;
	struct timeval tv;

	/* parameters for select() */
	FD_ZERO(&readfds);
	FD_SET(fdout, &readfds);

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	n = select(nfds, &readfds, (fd_set *)0, (fd_set *)0, &tv);
	ready_stdout = FD_ISSET(fdout, &readfds);
	if(!ready_stdout) return 0;		/* means timeout */

	n = read(fdout, bufp, RBUFSIZ-1);
	*(bufp+n) = '\0';
	return n;
}

int 
eval(char *bufp, char **argv)
{
	char *cp = bufp;
	char *token;
	int idx = 0;

	if(*cp != '(') return 0;
	cp += 1;
	while((token = strtok(cp, ",")) != NULL) {
	  if(token[0] == ')') break;
	  argv[idx++] = token;
	  cp = NULL;
	}
	return idx;
}

void * 
link2eic_read(void *p, int sz)
{
	char fmt[256];
	char msg[512];
	char rcvbuf[RBUFSIZ];
	int argc;
	char *argv[MAXARGS];
	int n;
	static val_t rdata;

	if(debug_mode) {
	  /* return fallback if not found */
	  rdata.llval = link2eic_lookup(p, sz, 0LL);
	  sprintf(fmt, "READ: @0x%%08x (sz=%%d) => 0x%%0%dllx\n", 2*sz);
	  printf(fmt, (unsigned int)p, sz, rdata.llval);
	}
	else {
	  sprintf(msg, "('read', 0x%08x, %d,)\n", (unsigned int)p, sz);
	  send_pipe(msg);
	  n = recv_pipe(rcvbuf);
	  if(n == 0) return NULL;
	  /* expecting "('rresp', resp, rdata,)\n" */
	  argc = eval(rcvbuf, argv); 
	  switch(sz) {
	  case 1: rdata.ucval = (unsigned char)strtoul(argv[2], NULL, 16); break;
	  case 2: rdata.usval = (unsigned short)strtoul(argv[2], NULL, 16); break;
	  case 4: rdata.ulval = strtoul(argv[2], NULL, 16); break;
	  case 8: rdata.ullval = strtoull(argv[2], NULL, 16); break;
	  default: rdata.ullval = 0LL;
	  }
	}

	return (void *)&rdata;
}

int
link2eic_write(void *p, int sz, void *pd)
{
	char fmt[256];
	char msg[512];
	char rcvbuf[RBUFSIZ];
	int argc;
	char *argv[MAXARGS];
	int n;
	unsigned long long wdata;

	switch(sz) {
	case 1: /* data is in ival/uival */
	case 2: /* data is in ival/uival */
	case 4: wdata = (unsigned long long)(*(unsigned int *)pd); break;
	case 8: wdata = (unsigned long long)(*(unsigned long long *)pd); break;
	default: wdata = 0LL;
	}

	if(debug_mode) {
	  sprintf(fmt, "WRITE: @0x%%08x (sz=%%d) <= 0x%%0%dllx\n", 2*sz);
	  printf(fmt, (unsigned int)p, sz, wdata);
	  return 0;
	}
	else {
	  sprintf(msg, "('write', 0x%08x, %d, 0x%llx,)\n", (unsigned int)p, sz, wdata);
	  send_pipe(msg);
	  /* expecting "('wresp', resp,)\n" */
	  n = recv_pipe(rcvbuf);
	  argc = eval(rcvbuf, argv); 
	  return n == 0 ? -1 : atoi(argv[1]);
	}
}

int
link2eic_iwait(int secs)
{
	fd_set readerrfds;
	struct timeval tv;
	struct timeval *ptv = NULL;

	/* substituted with sleep() in the standalone test mode */
	if (debug_mode) {
	  sleep(secs);
	  return 0;
	}

	/* parameters for select() */
	FD_ZERO(&readerrfds);
	FD_SET(fderr, &readerrfds);

	tv.tv_sec = secs;
	tv.tv_usec = 0;
	if(secs >= 0) ptv = &tv;

	return select(nfds, &readerrfds, (fd_set *)0, (fd_set *)0, ptv);
}

int
link2eic_fini(void)
{
	char msg[RBUFSIZ]; 

	if(fsm != ST_IDLE) {
	  /* sending out a 'fini' message */
	  sprintf(msg, "('fini', 0,)\n");
	  send_pipe(msg);
	}
	fsm = ST_IDLE;

	return 0; 
}

int
link2eic_tracelog(char *msg)
{
	char *buf; 

	if (debug_mode) return 0;

	buf = malloc(strlen(msg)+64);
	sprintf(buf, "('trace', 'log: %s',)\n", msg);
	send_pipe(buf);
	free(buf);

	return 0;
}

int
link2eic_ivec()
{
	int n, ready_stderr;
	int argc;
	char *argv[MAXARGS];
	fd_set readerrfds;
	struct timeval zero;
	char errrcvbuf[RBUFSIZ];
	char *bufp = errrcvbuf;

	/* parameters for select() */
	FD_ZERO(&readerrfds);
	FD_SET(fderr, &readerrfds);

	zero.tv_sec = 0;
	zero.tv_usec = 0;

	n = select(nfds, &readerrfds, (fd_set *)0, (fd_set *)0, &zero);
	ready_stderr = FD_ISSET(fderr, &readerrfds);
	if(!ready_stderr) return -2;		/* means empty-handed */

	/* decoded ivec value (in hex) */
	n = read(fderr, bufp, RBUFSIZ-1);
	if(n == 0) return -1;				/* means something went wrong */
	*(bufp+n) = '\0';
	argc = eval(bufp, argv);
	return strtoul(argv[1], NULL, 16);
}

int
link2eic_bgjob(int ival)
{
	int ivec;

	/* not bother to check if debug mode */
	if (debug_mode) return -1;

	ivec = link2eic_ivec();
#if 0
	if(ivec >= 0) 
	printf("ivec: %x\n", ivec);
#endif
	/* some bits are reserved for other use */ 
	return ivec & LINK2EIC_IMASK;
}

int 
link2eic_init_link(int port, int deferred_init)
{
	int nretries = 0;
	int n, len;
	char path2pipe[128];
	char rcvbuf[RBUFSIZ];
	int argc;
	char *argv[MAXARGS];
	int reason;

	/* -g => port=0 */
	if(port == 0) {
	  debug_mode = 1;
	  return 0;
	}

	/* -X (persistent mode) retries up to 5 secs */
	if(deferred_init == 'X') nretries = 10;

	/* open named pipes to start */
	while(1) {
	  /* create a path name */
	  sprintf(path2pipe, "/usr/tmp/link2eic-%d-", port);
	  len = strlen(path2pipe);
	  /* first open named pipes */
	  strcat(path2pipe, "stdin");
	  fdin  = open(path2pipe, O_WRONLY);
	  *(path2pipe+len)='\0'; strcat(path2pipe, "stdout");
	  fdout = open(path2pipe, O_RDONLY);
	  *(path2pipe+len)='\0'; strcat(path2pipe, "stderr");
	  fderr = open(path2pipe, O_RDONLY);

	  if(fdin == -1 || fdout == -1 || fderr == -1) {
	    /* retries for nretries times */
	    if(nretries == 0) {
	      printf("@E: Can't open the specified named pipes\n");
	      exit(1);
	    }
	    /* before trying again */
	    nretries -= 1;
	    usleep(RETRY_DELAY);
	    close(fdin);
	    close(fdout);
	    close(fderr);
	  }
	  else break;
	}

	/* maxDescPlus1 */
	nfds = max(fdout, fderr)+1;

	printf("@N: Pipes to link2eic are connected\n");
	fsm = ST_UP;

	/* sending 'init' may be deferred */
	/* this is to allow setting up simulation from C program */
	if(deferred_init) {
	  printf("@N: Co-sim link initialization is deferred due to -x option\n");
	  return 0;
	}

	/* initialize the connection */
	send_pipe("('init', 0,)\n");
	n = recv_pipe(rcvbuf);
	if(n == 0) {
	  printf("@E: Connection time out\n");
	  exit(1);
	}
	/* parse the message */
	argc = eval(rcvbuf, argv);
	if(!(argc >= 2 && (!strcmp(argv[0], "'ack'") || !strcmp(argv[0], "'nack'")))) {
	  printf("@E: Invalid response (%s)\n", argc <= 0 ? "" : argv[0]);
	  exit(1);
	}
	else if(!strcmp(argv[0], "'nack'")) {
	  reason = strtoul(argv[1], NULL, 16);
	  if(reason & 1)
	    printf("@E: Simulation is not ready\n");
	  else if(reason & 2)
	    printf("@E: Unable to process requests\n");
	  else
	    printf("@E: 'init' failed for unknown reason (0x%x)\n", reason);
	  exit(1);
	}
	else {
	  capability = strtoul(argv[1], NULL, 16);
	}
	fsm = ST_LINKED;

	return 0;
}

/*	Co-sim link initialization routine for deferred initialization

	returns:
	0  -> Co-sim link established
	-1 -> fatal error
	>0 -> attempt failed (reason returned)
*/

int link2eic_init_cosim(int nretries)
{
	int n;
	int reason;
	int argc;
	char *argv[MAXARGS];
	char rcvbuf[RBUFSIZ];

	/* maybe already up */
	if(fsm == ST_LINKED) return 0;

	while(1) {
	  /* initialize the connection */
	  send_pipe("('init', 0,)\n");
	  n = recv_pipe(rcvbuf);
	  if(n == 0) {
	    printf("@E: Connection time out\n");
	    return -1;
	  }
	  /* parse the message */
	  argc = eval(rcvbuf, argv);
	  if(!(argc >= 2 && (!strcmp(argv[0], "'ack'") || !strcmp(argv[0], "'nack'")))) {
	    printf("@E: Invalid response (%s)", argc <= 0 ? "" : argv[0]);
	    return -1;
	  }
	  else if(!strcmp(argv[0], "'nack'")) {
	    reason = strtoul(argv[1], NULL, 16);
	    /* retries for nretries times */
	    if(nretries == 0) return reason;
	    nretries -= 1;
	    usleep(RETRY_DELAY);
	  }
	  else {	/* 'ack' returned */
	    capability = strtoul(argv[1], NULL, 16);
	    fsm = ST_LINKED;
	    return 0;
	  }
	}
}

/* this returns the number of entries found in the file */

int
link2eic_loadVolatile(void)
{
	FILE *fp;
	struct stat st;
	int fsize;
	char *rdbuf;
	fitem_t infile;
	int n;

	if(access(volatile_data_file, R_OK) != 0) return 0;

	fp = fopen(volatile_data_file, "r");
	if(fp == NULL) return 0;

	fstat(fileno(fp), &st);
	fsize = st.st_size;

	rdbuf = (char *)malloc(fsize+1);
	fread(rdbuf, sizeof(char), fsize, fp);
	*(rdbuf+fsize)='\0';
	fclose(fp);

	/* this is to fool lexer() */
	EiC_Infile = &infile;
	CurrentFileName() = volatile_data_file;

	n = link2eic_parse(rdbuf);
	if(n) {
	  printf("@N: valid \'%s\' found\n", volatile_data_file);
	  printf("@N: %d predefined address-data sets were read\n", n); 
	}

	EiC_Infile = NULL;
	free(rdbuf);
	return n;
}

/* parsing the data file */

extern unsigned lex_lineno;

predefined_t anchor = { 0L, 0LL, NULL };

#define skip_line {curline = lex_lineno; ad = 0; continue;}

int link2eic_parse(char *rdbuf)
{
	int idx;
	char *cp, *ep;
	int t, ad;
	int curline;
	int n_entries = 0;
	unsigned long address;
	unsigned long long rdata;
	int header[] = { volatilesym, ASS, '{' };
	predefined_t *pentry;
	regex_t re;
	regmatch_t pm;
	int ret;

	/* skip until volatile = { ... */

	/* try to find where 'volatile = {' pattern starts */
	regcomp(&re,"^[ \t]*volatile[ \t]*[=][ \t]*[{]", REG_NEWLINE);

	ret = regexec(&re, rdbuf, (size_t)1, &pm, 0);
	regfree(&re);

	if(ret != 0) return 0;

	cp = rdbuf+pm.rm_so;
	ep = strchr(cp, '}');
	if(ep == NULL) return 0;
	*(ep+1) = '\0';

	EiC_initlex(cp);

	for(idx=0; idx < 3; ++idx) 
	  if(EiC_lexan() != header[idx]) return 0;

	curline = -1;
	ad = 0;
	while((t = EiC_lexan()) != '}') {
	  /* skip the rest of the line */
	  if(curline >= 0 && lex_lineno == curline) continue; 
	  if(t == '#') skip_line;
	  curline = -1;

	  switch(ad) {
	  case 0:
        if(!(t == INT || t == UINT)) skip_line;
 	    address = (unsigned long)token->Val.uival;
 	    ad += 1;
 	    break;
	  case 1:
        if(!(t == ':')) skip_line;
 	    ad += 1;
 	    break;
	  case 2:
        if(!(t >= INT && t <= ULLONG)) skip_line;
        if(t == INT || t == UINT) rdata = (unsigned long long)token->Val.uival;
 	    else rdata = (unsigned long long)token->Val.ullval;
	    /* creating a new entry */
	    pentry = (predefined_t *)malloc(sizeof(predefined_t));
	    pentry->address = address & ~0x7;
	    pentry->rdata = rdata;
	    pentry->next = NULL;
	    append_entry()->next = pentry;
	    n_entries += 1;
 	    ad += 1;
	    break;
	  case 3:
	    if(!(t == ',')) skip_line;
	    ad = 0;
	    break;
	  default:
	    break;
	  }

	}

	return n_entries;
}

predefined_t *append_entry()
{
	predefined_t *pp = &anchor;

	while(pp->next) {
	 pp = pp->next;
	}
	return pp;
}

unsigned long long link2eic_lookup(void *p, int sz, unsigned long long fallback)
{
	unsigned int masked_p = (unsigned int)p & ~0x7;	/* aligned on 64-bit boundaries */
	predefined_t *pp = &anchor;
	unsigned long long rdata;
	int found = 0;

	while(pp->next) {
	  pp = pp->next;
	  if(pp->address == masked_p) {
	    found = 1;
	    rdata = pp->rdata;
	    break;
	  }
	}

	if(!found) return fallback;

	/* Little-endian mapping */

	switch(sz) {
	case 1:
	  return (rdata >> (8*((unsigned int)p & 0x07))) & ((1LL << 8)-1);
	  break;  
	case 2:
	  return (rdata >> (8*((unsigned int)p & 0x06))) & ((1LL << 16)-1);
	  break;  
	case 4:
	  return (rdata >> (8*((unsigned int)p & 0x04))) & ((1LL << 32)-1);
	  break;  
	case 8:
      return rdata;
	  break;  
	default:
	  return 0LL;
	}
}
