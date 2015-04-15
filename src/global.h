/* global.h
 *
 *	(C) Copyright May  7 1995, Edmond J. Breen.
 *		   ALL RIGHTS RESERVED.
 * This code may be copied for personal, non-profit use only.
 *
 */
#ifndef GLOBALH
#define GLOBALH

#define  DONE   0
#define BSIZE 128
#define NONE -1
#define EOS  '\0'
#define TRUE    1
#define FALSE   0

typedef enum {/* the order of members in obj_t is important as it is
    	* reflected in the binary operator function table BINFUN in 
	* typesets.c 
        */
    t_error,   t_bool,    t_char,   t_uchar,   t_short, t_ushort,  /*5*/
    t_int,     t_enum,    t_uint,   t_long,    t_ulong, t_llong,   /*11*/
    t_ullong,  t_float,                                            /*13*/
    t_double,  t_pointer, t_void,   t_struct,  t_union,            /*18*/
    t_lval,    t_array,   t_func,   t_funcdec, t_elem,  t_eic,     /*24*/
    t_builtin, t_var,     t_hidden, t_ref
} obj_t;

/* unsafe macros */
#define isArithmetic(t) (t >= t_char && t <= t_double)
#define isIntegral(t)   (t >= t_char && t <= t_ulong)

typedef struct {
    char *id;
    int  token;
} keyword_t;

/* qualifiers */
enum {q_notset = 0,
	  q_const=2,
	  q_constp = 4,
	  q_volatile = 8,
	  q_volatilep = 16,
	  q_temp = 32,
          q_unsafe = 64};

/* storage class */
enum {c_auto=1,c_static=2,c_register=4,c_typedef=8,
	  c_extern=16, c_base=32, c_private=64, c_enum=128, c_global=256};

typedef enum { /* keyword symbols */
    autosym = 300,
    breaksym, casesym, charsym, constsym, continuesym,        /*305*/
    defaultsym, dosym, doublesym, eiclongjmpsym, eicsetjmpsym, elsesym, enumsym, externsym, /*313*/
    floatsym, forsym, gotosym, idsym, ifsym, intsym, longsym, /*320*/
    registersym, returnsym, safesym, shortsym,  signedsym, sizeofsym, /*326*/
    staticsym, structsym, switchsym, typedefsym, unionsym,    /*331*/
    unsignedsym, unsafesym, voidsym, volatilesym, whilesym    /*336*/
} keysyms_t;


#include "typemod.h"
#include "datastruct.h"

/* backward compatibility flag */
extern int __backward__;

extern environ_t * EiC_ENV;

                   /*CUT nameSpaceCodes*/
extern int EiC_work_tab;
enum{ /* name space codes */
	eic_tab,   /* name space for EiC commands */
	stand_tab, /* name space for basic variables */
	tag_tab,   /* name space for struct/union and enumeration tags */
	lab_tab    /* name space for goto labels */
    };
                   /*END CUT*/ 

enum {eickmark, eicgstring, eicstay};


#endif








