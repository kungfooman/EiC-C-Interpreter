#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST eng.c");
    system("eic -g -DTEST err_exit.c");
    system("eic -g -DTEST fcompare.c fcompare.c   fcompare.c");
    system("eic -g -DTEST fibo.c");
    system("eic -g -DTEST fmtmoney.c  3303.50");
    system("eic -g -DTEST fraction.c 0.37931034");
    system("eic -g -DTEST hash.c");
    system("eic -g -DTEST ipow.c 8 4");
    system("eic -g -DTEST ispow2.c");

    return 0;
}

#ifdef EiCTeStS
main();
#endif
