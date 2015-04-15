#include <stdlib.h>
int main()
{
    system("eic -g -sA < testMemErr2.aux");
    system("eic -g -sA < testMemErr2b.aux");
    system("eic -g -sA < testMemErr2c.aux");
    return 0;
}

#ifdef EiCTeStS
main();
#endif
