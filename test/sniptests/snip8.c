#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST bincomp.c bincomp.c bincomp.c");
    system("eic -g -DTEST head.c head.c 7");
    system("eic -g -DTEST tiresize.c 265 75 16"); 
    system("eic -g -DTEST strupr.c hello world");
    system("eic -g -DTEST skiplist.c ");
    system("eic -g -DTEST remtab.c  < remtab.c");
    system("eic -g -DTEST spigot.c 13");
    system("eic -g -DTEST rand1.c");
    system("eic -g -DTEST regit.c DougFunny");

    return 0;
}

#ifdef EiCTeStS
main();
#endif
