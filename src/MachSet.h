/* MachSet.h
 *
 *	(C) Copyright May  7 1995, Edmond J. Breen.
 *		   ALL RIGHTS RESERVED.
 * This code may be copied for personal, non-profit use only.
 *
 */

typedef enum { /* Stack Machine Instruction Set */
  halt=400,

  bump,

  /* If jumps are altered, added to or rearranged,
   * then check with the routine analyseCode -
   * in file optomizer.c
   */

  __eicsetjmp, __eiclongjmp,

  jmptab, jmpu,
  jmpFint, jmpFlng,  jmpFdbl, jmpFptr, jmpFllng,
  jmpTint, jmpTlng,  jmpTdbl, jmpTptr, jmpTllng,
  

  dupval,dupdown,
  lval,

  ixa,

  /* get operators */
  rvalchar,rvaluchar,
  rvalshort,rvalushort,
  rvalint,rvaluint,
  rvallong,rvalulong,
  rvalllong,rvalullong,
  rvalptr,rvaluptr,
  rvalfloat,rvaldouble,

 
  /* store operator */
  stochar,
  stoshort,
  stoint,stouint,
  stolong,stoulong,
  stollong,stoullong,stouptr,
  stoptr,
  stofloat,stodouble,
  stoval,


  incdouble, decdouble,
  pushdouble,
  drefdouble, refdouble,
  negdouble, adddouble, subdouble, divdouble, multdouble,
  ltdouble, ledouble, eqdouble, nedouble, gtdouble,
  gedouble, lordouble, landdouble, notdouble,
  double2char, double2int, double2long, double2llong, double2ullong, double2float,


  incint, decint,
  pushint,
  drefint, refint,
  drefvolint, refvolint,	/* volatile storage */
  negint, addint, subint, divint, multint,
  ltint, leint, eqint, neint, gtint,
  geint, lorint, landint, notint, andint, borint,
  xorint, modint, lshtint, rshtint, compint,
  int2uchar, int2ushort, int2ptr, int2double,
  int2long, int2llong, int2ullong,

  incuint, decuint,
    pushuint,
  drefuint, refuint,
  drefvoluint, refvoluint,	/* volatile storage */
  neguint, adduint, subuint, divuint, multuint,
  ltuint, leuint, equint, neuint, gtuint,
  geuint, loruint, notuint, anduint, boruint,
  xoruint, moduint, lshtuint, rshtuint, compuint,
  uint2char, uint2ptr, uint2double,
  uint2long, uint2llong, uint2ullong,

  inclong, declong,
    pushlong,
  dreflong, reflong,
  drefvollong, refvollong,	/* volatile storage */
  neglong, addlong, sublong, divlong, multlong,
  ltlong, lelong, eqlong, nelong, gtlong,
  gelong, lorlong, landlong, notlong, andlong, borlong,
  xorlong, modlong, lshtlong, rshtlong, complong,
  long2char, long2int, long2ptr, long2double,
  long2llong, long2ullong,

  inculong, deculong,
    pushulong,
  drefulong, refulong,
  drefvolulong, refvolulong,	/* volatile storage */
  negulong, addulong, subulong, divulong, multulong,
  ltulong, leulong, equlong, neulong, gtulong,
  geulong, lorulong, notulong, andulong, borulong,
  xorulong, modulong, lshtulong, rshtulong, compulong,
  ulong2char, ulong2int, ulong2ptr, ulong2double,
  ulong2llong, ulong2ullong,

  incllong, decllong,
  incullong, decullong,
    pushllong, pushullong,
  drefllong, refllong,
  drefullong, refullong,
  drefvolllong, refvolllong,	/* volatile storage */
  drefvolullong, refvolullong,	/* volatile storage */
  negllong, addllong, subllong, divllong, multllong,
  ltllong, lellong, eqllong, nellong, gtllong,
  gellong, lorllong, landllong, notllong, andllong, borllong,
  xorllong, modllong, lshtllong, rshtllong, compllong,
  negullong, addullong, subullong, divullong, multullong,
  ltullong, leullong, equllong, neullong, gtullong,
  geullong, lorullong, landullong, notullong, andullong, borullong,
  xorullong, modullong, lshtullong, rshtullong, compullong,
  llong2char, llong2int, llong2long, llong2ptr, llong2double,
  ullong2char, ullong2int, ullong2long, ullong2ptr, ullong2double,
  

  drefptr, refptr, incptr, decptr,
        pushptr,
  addptr2int, addint2ptr, subptrint,
  subptr, divptr,
  ltptr, leptr, eqptr, neptr, gtptr,
  geptr, lorptr, landptr, notptr,
  ptr2int, ptr2long,

  drefuchar, drefchar, refchar,  neguchar,
  drefvoluchar, drefvolchar, refvolchar,	/* volatile storage */
   
  
  char2int, char2ptr, char2double,
  
  drefushort, drefshort, refshort,
  drefvolushort, drefvolshort, refvolshort,	/* volatile storage */
   
  
  
  dreffloat, reffloat,
   

  assigntype,  pushval,
  massign,  fmem, mset, minit,
  refmem, reducear, checkar, checkar2,
  call, eiccall, endfunc, eicreturn, empty,
  bgjob,

  lda,


  /* unique unsafe pointer instructions */
    drefuptr, refuptr


} MachSet_t;


#define IsSto_op(x)  ((x) >= stochar && (x)<=stoval)









