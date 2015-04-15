/*****************************************************************************
 *****************************************************************************
    $Id: //depot/easycosim/cint/EiC/new_main/examples/test-datatypes.c#1 $
        (@project_name@) @explanational_name@

        by neko

    Description:
        This simple program is provided to verify if the EiC was compiled
		for _ILP32 Unix system. Many changes made assumed the target system 
		was _ILP32 Unix system (to match the target 64-bit AXI system) 

    History:
		4/05/2009: Created
 *****************************************************************************
 *****************************************************************************/
#include <stdio.h>
#include <assert.h>

int 
main()
{
	printf("It pukes if the EiC was not compiled for _ILP32 Unix system\n");
	printf("Testing char, short, int, long, long long, ptr data types ...\n\n");
	// no assertion error if it is running on a _ILP32 Unix system
	assert(sizeof(char) == 1);
	assert(sizeof(unsigned char) == 1);
	assert(sizeof(short) == 2);
	assert(sizeof(unsigned short) == 2);
	assert(sizeof(int) == 4);
	assert(sizeof(unsigned int) == 4);
	assert(sizeof(long) == 4);
	assert(sizeof(unsigned long) == 4);
	assert(sizeof(long long) == 8);
	assert(sizeof(unsigned long long) == 8);
	// unsafe ptr is "naked" ptr 
	assert(sizeof(void * unsafe) == 4);

	// endianness
	printf("Endianness: %s-endian\n", __LITTLE_ENDIAN__ ? "Little" : "Big");

	return 0;
}
