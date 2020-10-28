/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include "efm32gg.h"

/*
 * gamepad_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

/* Global attributes */
struct class *gamepad_cls;
dev_t devno;
struct cdev gamepad_cdev;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = gamepad_read,
	.write = gamepad_write,
	.open = gamepad_open,
	.release = gamepad_release
};
char buttons_value; //FIXME put that somewhere else

static int __init gamepad_init(void)
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

	//character device allocations
	err	= alloc_chrdev_region(&devno, 0, DEVCNT, DEVNAME);
	if(err<0) {
		printk(KERN_WARNING"Error while allocating the device (%d)\n", err);
		return err;
	}
	cdev_init(&dev.gamepad_cdev, &fops);
	dev.gamepad_cdev.owner = THIS_MODULE;
	dev.gamepad_cdev.ops = &fops;
	err = cdev_add(&dev.gamepad_cdev, devno, 1);
	if(err<0) {
		printk(KERN_WARNING"Error while adding the char device %s (%d)\n", DEVNAME, err);
	}

	gamepad_cls = class_create(THIS_MODULE, DEVNAME);
	if(!gamepad_cls) {
		printk(KERN_WARNING"Error while creating the device class for %s\n", DEVNAME);
		return -1;
	}
	gamepad_cls->devnode = gamepad_devnode;

	if(!device_create(gamepad_cls, NULL, devno, NULL, DEVNAME)) {
		printk(KERN_WARNING"Error while creating the device for %s\n", DEVNAME);
		return -1;
	}

	return 0;
}

static int gamepad_open(struct inode *inode, struct file *filp) {
	printk(KERN_INFO"Device file has been opened\n");
	return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp) {
	printk(KERN_INFO"Device file has been closed\n");
	return 0;
}

static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	buttons_value = 0xff; //TODO implement the interrupt to populate this (and remove this line)
	printk(KERN_INFO"Buttons value is %x\n", buttons_value);
	if(*offp >= 1) return 0; //EOF
	if(copy_to_user(buff, &buttons_value, 1)) {
		printk(KERN_WARNING"Missing some bytes, failing\n");
		return -EFAULT;
	}
	*offp++; //1 byte read
	return READ_SIZE;
}

static ssize_t gamepad_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
	char val;
	if(*offp >= 1) return 0; //EOF
	if(copy_from_user(&val, buff, 1)) {
		printk(KERN_WARNING"Missing some bytes, failing\n");
		return -EFAULT;
	}
	printk(KERN_INFO"User value is %x\n", val); //dummy thing
	offp++;
	return count; //fake to read it all
}

/*
 * gamepad_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit gamepad_cleanup(void)
{
	 printk(KERN_INFO"Cleaning up the devices\n");
	 device_destroy(sound_cls, devno);
	 class_destroy(sound_cls);
	 cdev_del(&dev.sound_cdev);
	 unregister_chrdev_region(devno, DEVCNT);
}

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

