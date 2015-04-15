#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST arccrc16.c arccrc16.c");
    system("eic -g -DTEST bcdl.c");
    system("eic -g -DTEST bcdd.c");
    system("eic -g -DTEST bitstrng.c");
    system("eic -g -DTEST bodymass.c  67 175");
    system("eic -g -DTEST ccard.c 38437534974933");
    
    return 0;
}

#ifdef EiCTeStS
main();
#endif
