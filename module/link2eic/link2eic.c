#include <stdlib.h>
#include <unistd.h>
#include "../../new_main/link2eic.h"
#include "eic.h"

/*
	int link2eic_iwait(secs)

	blocking until a message is arrived to stderr pipe stream
	if secs is a negative, it will wait indefinitely (no timeout)
*/

val_t eic_link2eic_iwait(void)
{
    val_t v;

	v.ival = link2eic_iwait(arg(0,getargs(),int));
	return v;
}

/*
	void link2eic_tracelog(msg)

	send out the message to stdin pipe stream using the 'trace'
    command. The message is logged to the agent's logging file.

*/

val_t eic_link2eic_tracelog(void)
{
    val_t v;

	v.ival = link2eic_tracelog(arg(0,getargs(),char *));
	return v;
}

/*
	int link2eic_init_cosim(nretries)

	try to initialize the Co-sim link to simulation
	up to nretries times (every 0.5 secs)
	this is for deferred initialization
	returns -1 (fatal error), 0 (success), >0 (failed for reason)
*/

val_t eic_link2eic_init_cosim(void)
{
	val_t v;

	v.ival = link2eic_init_cosim(arg(0,getargs(),int));
	return v;
}

/****************************************************************/

void module_link2eic(void)
{

    EiC_add_builtinfunc("link2eic_iwait",eic_link2eic_iwait);
    EiC_add_builtinfunc("link2eic_tracelog",eic_link2eic_tracelog);
	EiC_add_builtinfunc("link2eic_init_cosim",eic_link2eic_init_cosim);
}
