/*****************************************************************************
 *****************************************************************************
    $Id: //depot/easycosim/cint/EiC/new_main/link2eic.h#9 $
        (@project_name@) @explanational_name@

        by @designer_name@

    Description:
        @Module_functional_summary@

    History:
        @mm/dd/yy@: @description@
 *****************************************************************************
 *****************************************************************************/

#ifndef LINK2EICH_
#define LINK2EICH_

#define LINK2EIC_DEFAULT_PORT	17767
#define LINK2EIC_IMASK ~(1 << 15)

int link2eic_init_link(int port, int deferred);

void *link2eic_read(void *p, int sz);
int link2eic_write(void *p, int sz, void *pd);

int link2eic_bgjob(int ival);
int link2eic_ivec();

int link2eic_iwait(int secs);
int link2eic_fini(void);
int link2eic_tracelog(char *msg);
int link2eic_init_cosim(int nretries);

int link2eic_loadVolatile(void);
int link2eic_parse(char *rdbuf);

typedef struct predef_t {
  unsigned int address;
  unsigned long long rdata;
  struct predef_t *next;
} predefined_t;

predefined_t *append_entry();
unsigned long long link2eic_lookup(void *p, int sz, unsigned long long fallback);


#endif /* LINK2EICH_ */
