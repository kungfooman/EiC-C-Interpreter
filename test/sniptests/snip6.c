#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST crc_32.c"); 
    system("eic -g -DTEST ansiflen.c ansiflen.c"); 
    system("eic -g -DTEST bitcnt_1.c 1313131212"); 
    system("eic -g -DTEST bitcnt_2.c 1313131212"); 
    system("eic -g -DTEST bitcnt_3.c 1313131212"); 
    system("eic -g -DTEST bitcnt_4.c 1313131212"); 
    system("eic -g -DTEST bstr_i.c  100110101111"); 

    return 0;
}

#ifdef EiCTeStS
main();
#endif
