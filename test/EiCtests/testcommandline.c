
#include <stdlib.h>

int main(void)
{
    system("eic -g 'testcommandline.aux' abc 123 \"  hello   world\" this.and.that");
    return 0;
}


#ifdef EiCTeStS
main();
#endif
