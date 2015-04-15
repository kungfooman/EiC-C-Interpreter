/* this file is for creating a version of EiC which
 *  does not link to its implementation of the
 *  standard C library nor does it use readline.
 *
 *
 * To build this version:
 *		
 * 		make -f makefile.ppc 
 *
 *  which makes the executabe seic, (small eic) and seic.sr (an S-record)
 *
 */


#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "eic.h"
#include "../module/stdClib/src/stdClib2eic.h" 
#include "preproc.h"

#define str(x)  #x
#define xstr(x) str(x)

#ifdef POWERPC
void prs(char *str);
val_t eic_gets(void);
val_t eic_puts(void);
val_t eic_getch(void);
val_t eic_putch(void);
val_t eic_getchq(void);
val_t eic_in(void);
val_t eic_out(void);
val_t eic_load(void);

extern char *startstr;

static char loadstring[4096]="

void puts(char *str);
char *gets(char *str);
int getch(void);
void putch(int ch);
int getchq(void);
int in(unsigned long addr);
void out(unsigned char val, unsigned long addr);
int load(char *str);
int printf(const char *fmt, ...);
int sprintf(char *buf, const char * fmt, ...);
int scanf(const char *fmt, ...);
int sscanf(const char *str,const char *fmt, ...);

typedef unsigned size_t;

void *memmove(void * dst, const void * src , size_t n);
char *strcpy(char * dst, const char * src);
char *strncpy(char * dst, const char * src, size_t n);
char *strcat(char * s1, const char * s2);
char *strncat(char * s1, const char *s2, size_t n);
int memcmp(const void * s1, const void * s2, size_t n);
int strcmp(const char * s1, const char * s2);
int strcoll(const char * s1, const char * s2);
int strncmp(const char * s1, const char *s2, size_t n);
size_t strxfrm(char *dst, const char * src, size_t n);
void *memchr(const void *s, int c, size_t n);
char *strchr(const char *s, int c);
size_t strcspn(const char *s, const char *reject);
char *strpbrk(const char *s, const char *accept);
char *strrchr(const char *s, int c);
size_t strspn(const char *s, const char *accept);
char *strstr(const char *haystack, const char *needle);
char *strtok(char *s, const char *delim);
void *memset(void *s, int c, size_t n);
char *strerror(int n);
size_t strlen(const char *s);
char * strrev(char * s);

#define RAND_MAX 32767
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define MB_CUR_MAX 1

typedef struct { int quot, rem; }div_t;

typedef struct { long quot, rem; }ldiv_t;

div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
void * malloc(size_t n);
void * calloc(size_t x, size_t y);
void * realloc(void * ptr, size_t n);
#define  free(x)  (free)(&(x));
void  (free)(void *ptr);
#define strtoul(x,y,z) strtol(x,y,z)
int rand(void);
void srand(unsigned int seed);
double strtod(const char *str, char **endptr);
long strtol(const char *str, char **endptr,int base);

int atoi(const char *s);
double atof(const char *str);
long atol(const char *s);
void abort(void);
char * _itoa(int n,char *str, int radix, int mod);
char * _ltoa(int n,char *str, int radix, int mod);
char *fftoa(double d, char *str, int p, char type, int trunc);
#define itoa(x,y,z)     _itoa(x,y,z,1)
#define utoa(x,y,z)     _itoa(x,y,z,2)
#define ltoa(x,y,z)     _ltoa(x,y,z,1)
#define ultoa(x,y,z)	_ltoa(x,y,z,2)


double acos(double a);
double asin(double a);
double atan(double a);
double atan2(double a, double b);
double cos(double a);
double sin(double a);
double tan(double a);
double cosh(double a);
double sinh(double a);
double tanh(double a);
double exp(double a);
double frexp(double a, int * b);
double ldexp(double a, int b);
double log(double a);
double log10(double a);
double modf(double a, double *b);
double pow(double a, double b);
double sqrt(double a);
double ceil(double a);
double fabs(double a);
double floor(double a);
double fmod(double a, double b);
puts(\"\\nDone loading prototypes...\");
";


#endif

int  main(int argc, char ** argv)
{

    EiC_init_EiC();

    /* the macro PLATFORM 
     * is passed in by the 
     * compiler
     */

    dodefine("_EiC");
    dodefine(&(xstr(PLATFORM)[1]));
    #ifdef PPCLIB
    prs("Starting EiC...\n");
    setvbuf(stdout,NULL,_IONBF,0);
    add_builtinfunc("puts",eic_puts);
    add_builtinfunc("gets",eic_gets);
    add_builtinfunc("putch",eic_putch);
    add_builtinfunc("getch",eic_getch);
    add_builtinfunc("getchq",eic_getchq);
    add_builtinfunc("in",eic_in);
    add_builtinfunc("out",eic_out);
    add_builtinfunc("load",eic_load);
    
    add_builtinfunc("printf",eic_printf);
    add_builtinfunc("sprintf",eic_sprintf);
    add_builtinfunc("scanf",eic_scanf);
    add_builtinfunc("sscanf",eic_sscanf);
    add_builtinfunc("setvbuf",eic_setvbuf);
    
      /* string .h */
    add_builtinfunc("memcpy",eic_memcpy);
    add_builtinfunc("memmove",eic_memmove);
    add_builtinfunc("strcpy",eic_strcpy);
    add_builtinfunc("strncpy",eic_strncpy);
    add_builtinfunc("strcat",eic_strcat);
    add_builtinfunc("strncat",eic_strncat);
    add_builtinfunc("memcmp",eic_memcmp);
    add_builtinfunc("strcmp",eic_strcmp);
    add_builtinfunc("strcoll",eic_strcoll);
    add_builtinfunc("strncmp",eic_strncmp);
    add_builtinfunc("strxfrm",eic_strxfrm);
    add_builtinfunc("memchr",eic_memchr);
    add_builtinfunc("strchr",eic_strchr);
    add_builtinfunc("strcspn",eic_strcspn);
    add_builtinfunc("strpbrk",eic_strpbrk);
    add_builtinfunc("strrchr",eic_strrchr);
    add_builtinfunc("strspn",eic_strspn);
    add_builtinfunc("strstr",eic_strstr);
    add_builtinfunc("strtok",eic_strtok);
    add_builtinfunc("memset",eic_memset);
    add_builtinfunc("strerror",eic_strerror);
    add_builtinfunc("strlen",eic_strlen);  
    add_builtinfunc("strrev", eic_strrev);
    
     /* stdlib.h */
    add_builtinfunc("_itoa", eic_itoa);
    add_builtinfunc("_ltoa", eic_ltoa);
    add_builtinfunc("fftoa", eic_fftoa);
    add_builtinfunc("malloc", eic_malloc);
    add_builtinfunc("calloc", eic_calloc);
    add_builtinfunc("realloc", eic_realloc);
    add_builtinfunc("free", eic_free);
    add_builtinfunc("strtod", eic_strtod);
    add_builtinfunc("strtol", eic_strtol);
    add_builtinfunc("strtoul", eic_strtoul);
    add_builtinfunc("rand", eic_rand);
    add_builtinfunc("srand", eic_srand);
    add_builtinfunc("atoi", eic_atoi);
    add_builtinfunc("atof", eic_atof);
    add_builtinfunc("atol", eic_atol);
    add_builtinfunc("abort",eic_exit);

    add_builtinfunc("eic_exit",eic_exit);

    add_builtinfunc("div",eic_div);
    add_builtinfunc("ldiv",eic_ldiv);
    add_builtinfunc("acos",eic_acos);
    add_builtinfunc("asin",eic_asin);
    add_builtinfunc("atan",eic_atan);
    add_builtinfunc("atan2",eic_atan2);
    add_builtinfunc("cos",eic_cos);
    add_builtinfunc("sin",eic_sin);
    add_builtinfunc("tan",eic_tan);
    add_builtinfunc("cosh",eic_cosh);
    add_builtinfunc("sinh",eic_sinh);
    add_builtinfunc("tanh",eic_tanh);
    add_builtinfunc("exp",eic_exp);
    add_builtinfunc("frexp",eic_frexp);
    add_builtinfunc("ldexp",eic_ldexp);
    add_builtinfunc("log",eic_log);
    add_builtinfunc("log10",eic_log10);
    add_builtinfunc("modf",eic_modf);
    add_builtinfunc("pow",eic_pow);
    add_builtinfunc("sqrt",eic_sqrt);
    add_builtinfunc("ceil",eic_ceil);
    add_builtinfunc("fabs",eic_fabs);
    add_builtinfunc("floor",eic_floor);
    add_builtinfunc("fmod",eic_fmod);


    startstr=loadstring; /* load defines */
    
    /* strcat(startstr,"typedef struct {void *p, *sp, *ep;} ptr_t;\n");
    strcat(startstr,"typedef struct { ptr_t _ptr; int _cnt; ptr_t _base;\\\n");
    strcat(startstr,"unsigned short _flag; short _fd; unsigned long _pid;\\\n");
    strcat(startstr,"unsigned  _bsize; ptr_t _tmpnam; char _sbuf[4];\\\n");
    strcat(startstr,"unsigned _entry; }FILE;\n");

    strcat(startstr,"int fgetc(FILE * fp);\n");
    strcat(startstr,"int fputc(int c, FILE * fp);\n");
    strcat(startstr,"char * fgets(char *s, int n, FILE *fp);\n");
    strcat(startstr,"int fputs(const char *s, FILE *fp);\n");  */

    #endif
    EiC_startEiC(argc, argv);
    return 0;
}
