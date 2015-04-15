#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST rdxcnvrt.c 2013 10 3");    
    system("eic -g -DTEST strdel.c helloworld pos 2 3");
    system("eic -g -DTEST strdelch.c eo helloworld");
    system("eic -g -DTEST c_cmnt.c < c_cmnt.c"); 
    system("eic -g -DTEST strrev.c DougFunny");
    system("eic -g -DTEST etphi.c 11"); 

    return 0;
}

#ifdef EiCTeStS
main();
#endif
