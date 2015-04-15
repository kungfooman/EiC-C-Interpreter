#include <stdio.h>
#include <stdlib.h>

#define tmp "tabc11"

int main()
{

    system("ln -s tst1.c " tmp);
    system("eic -g filetype.c .. filetype.c " tmp);
    system("eic -g unlink.c ");


    system("touch foo bar");
    system("eic -g changemod.c");
    system("rm foo bar");

    
    remove(tmp);
    return 0;
}
