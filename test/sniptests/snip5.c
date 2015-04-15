#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST pbmsrch.c");
    system("eic -g -DTEST rad2deg.c");
    system("eic -g -DTEST rg_rand.c");
    system("eic -g -DTEST rnd_div.c 333 22");
    system("eic -g -DTEST roman2l.c MCIV");
    system("eic -g -DTEST ruleline.c");
    system("eic -g -DTEST soundex.c helloworld");
    system("eic -g -DTEST stptok.c ItsaniceDay iD");
    system("eic -g -DTEST stristr.c");
    system("eic -g -DTEST strrpbrk.c");
    system("eic -g -DTEST vfname.c");
    system("eic -g -DTEST w_wrap.c");

    return 0;
}

#ifdef EiCTeStS
main();
#endif
