#include <stdlib.h>

int main(void)
{
    system("eic -g -DTEST checksum.c");
    system("eic -g -DTEST combin.c   6 2");
    system("eic -g -DTEST crc_16f.c  crc_16f.c");
    system("eic -g -DTEST cubic.c");
    system("eic -g -DTEST daynum.c   11 13 57");
    system("eic -g -DTEST dow.c 57 11 13");
    system("eic -g -DTEST dbl2long.c  13.13");

    return 0;
}

#ifdef EiCTeStS
main();
#endif
