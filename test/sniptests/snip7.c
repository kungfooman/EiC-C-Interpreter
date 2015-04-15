#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST easter.c 1997"); 
    system("eic -g -DTEST dblround.c 167.5678"); 
    system("eic -g -DTEST factoryl.c");  
    system("eic -g -DTEST sstrdel.c"); 
    system("eic -g -DTEST trim.c \" trim     test\"");  
    system("eic -g -DTEST amalloc.c"); 
    return 0;
}

#ifdef EiCTeStS
main();
#endif
