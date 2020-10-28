/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include "efm32gg.h"

/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init template_init(void)
{
	printk("Hello World, here is your module speaking\n");
	//Enable GPIO clock
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;

	//BUTTONS
	*GPIO_PC_MODEL = 0x33333333;	/*Setting pins as input pins */
	*GPIO_PC_DOUT = 0xff;	/*Internal pull-ip resistors for the buttons */

	//Interrupt handling GPIO

	//Setting BUTTON port to allow interrupts (Port C)
	*GPIO_EXTIPSELL = 0x22222222;

	//Enables interrupts on rise and fall values, and interrupt generation
	// from the GPIO
	*GPIO_IEN = 0xff;	//enable generation
	//*GPIO_EXTIRISE = 0xff;	//enable generation on rise
	*GPIO_EXTIFALL = 0xff;	//enable generation on fall

	return 0;
}

/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit template_cleanup(void)
{
	 printk("Short life for a small module...\n");
}

module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

