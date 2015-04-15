#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST jdn_l.c 13 11 57");
    system("eic -g -DTEST l2roman.c  1345");
    system("eic -g -DTEST logscale.c");
    system("eic -g -DTEST match.c ell hello");
    system("eic -g -DTEST mathstat.c 12 13 14 15");
    system("eic -g -DTEST maxline.c helloworldhow");
    system("eic -g -DTEST memmem.c");
    system("eic -g -DTEST moon_age.c 11 13 57");
    system("eic -g -DTEST parity.c 13456");
    system("eic -g -DTEST parstime.c 12:30:30");

    return 0;    
}

#ifdef EiCTeStS
main();
#endif
