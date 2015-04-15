#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>

void do_fileflags()
{
    system("eic -g fileflags.c fileflags.c");
    system("eic -g fileflags.c  0 < /dev/tty");
    system("eic -g fileflags.c  1 > temp.foo");
    system("cat temp.foo");
    system("eic -g fileflags.c  2 2>>temp.foo");
    remove("temp.foo");
}

void do_filetype()
{
    system("eic -g filetype.c filetype.c /usr /etc");
}


void do_access()
{
    system("eic -g access.c");
    system("eic -g access.c access.c");
}

void do_unistd()
{
    system("eic -g seek.c < seek.c");
    system("eic -g hole.c");
    system("od -c file.hole");
    sleep(1);
    remove("file.hole");
    system("eic -g mycat.c < mycat.c");
}
int main(void)
{
    do_fileflags();
    do_filetype();
    do_access();
    do_unistd();
    return 0;
}

#ifdef EiCTeStS
main();
#endif












