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
#include <linux/random.h>


#define DRIVER_AUTHOR "Hrvoje Novosel <hrvojedotnovosel@gmail.com>"
#define DRIVER_DESC   "Simple kernel module for testing technical skills of newcomers by pseudo-randomly shutting down the machine."

#define SUCCESS_RANGE 10

// module settings
static short int timeout = 30;
static short int succes_prob = 3;

module_param(timeout, short, 0);
MODULE_PARM_DESC(timeout, "Timeout between probing for shutdown event");
module_param(succes_prob, short, 0);
MODULE_PARM_DESC(succes_prob, "Probability of shutdown event occurring, range 0..9 inclusive");

struct timer_list call_timer;
char call_status = 0;


static void timer_function( unsigned long ptr )
{
	printk(KERN_INFO "Call to timer fnc achieved! Count:%i\n", (unsigned int)call_status);
	call_status++;

	// random number is needed
	unsigned int r, modr;
	get_random_bytes( &r, sizeof(r) );
	modr = r % SUCCESS_RANGE;
	printk(KERN_INFO "Got random no: %i\n", modr);
	if( modr < succes_prob ){
		// and system address of kernel shutdown rutine
		printk(KERN_INFO "SHUT DOWN THE COMP\n",);
	}

	call_timer.expires = jiffies + (HZ * timeout);
	add_timer( &call_timer );
}


static int __init kshoutdown_init ( void )
{

	printk(KERN_INFO "Random shutdown module has been loaded, shutdown event probability of %i every %i seconds.\n", succes_prob, timeout);

	init_timer( &call_timer );
	call_timer.function = timer_function;
	call_timer.data     = (unsigned long) &call_status;
	call_timer.expires  = jiffies + (HZ * timeout);
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