/*
*
*   Randomly, with chance of .3 every 30 min, shutdown computer from kernel space. 
*     Excellent test for newcomers, install kernel module and see if they are able to pinpoint why their computer chases.
*
*    Created: 30. Jun 2017
*    Author: Hrvoje Novosel<hrvojedotnovosel@gmail.com>
*
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


#define DRIVER_AUTHOR "Hrvoje Novosel <hrvojedotnovosel@gmail.com>"
#define DRIVER_DESC   "Simple kernel module for testing technical skills of newcomers by pseudo-randomly shutting down the machine."


// module settings
static short int timeout = 30;
static short int succes_prob = 3;

module_param(timeout, short, 0);
MODULE_PARM_DESC(timeout, "Timeout between probing for shutdown event");
module_param(succes_prob, short, 0);
MODULE_PARM_DESC(succes_prob, "Probability of shutdown event occurring, range 0..9 inclusive");


struct timer_list call_timer;
char call_status = 0;

#define CALL_DELAY HZ/5

static void timer_function( unsigned long ptr )
{
	printk(KERN_INFO "Call to timer fnc achieved!");
	call_timer.expires = jiffies + CALL_DELAY;
	add_timer( &call_timer );
}


static int __init kshoutdown_init ( void )
{

	printk(KERN_INFO "Random shutdown module has been loaded, shutdown event probability of %i every %i seconds.\n", succes_prob, timeout);

	convert of timeout to seconds is needed next!

	init_timer( &call_timer );
	call_timer.function = timer_function;
	call_timer.data     = (unsigned long) &call_status;
	call_timer.expires  = jiffies + timeout;
	add_timer( &call_timer );
	return 0;

}


static void __exit kshoutdown_exit( void )
{
	printk(KERN_INFO "Shutdown module unload\n");
	del_timer( &call_timer );
}


module_init(kshoutdown_init);
module_exit(kshoutdown_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);