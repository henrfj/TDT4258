#include "driver-gamepad.h"
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
char buttons_value;

/*
 * Initialization of the hardware registers and kernel data structures.
 * Here the kernel is instructed to create the character device and to
 * export it as desired.
 * A common IRQ handler is also registered to both the GPIO channels
 */
static int __init gamepad_init(void)
{	
	int err;

	printk("Hello World??? :D here is your module speaking\n");

	
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
	*GPIO_EXTIRISE = 0xff;	//enable generation on rise
	*GPIO_EXTIFALL = 0xff;	//enable generation on fall

	//character device allocations
	
	//Allocate the device by requesting MIN and MAJ numbers
	err	= alloc_chrdev_region(&devno, 0, DEVCNT, DEVNAME);
	if(err<0) {
		printk(KERN_WARNING"Error while allocating the device (%d)\n", err);
		return err;
	}
	//Initialize the character device with file operations (functions here defined)
	cdev_init(&gamepad_cdev, &fops);
	gamepad_cdev.owner = THIS_MODULE;
	gamepad_cdev.ops = &fops;
	err = cdev_add(&gamepad_cdev, devno, 1);
	if(err<0) {
		printk(KERN_WARNING"Error while adding the char device %s (%d)\n", DEVNAME, err);
	}

	//create the device class to export it to the userspace
	gamepad_cls = class_create(THIS_MODULE, DEVNAME);
	if(!gamepad_cls) {
		printk(KERN_WARNING"Error while creating the device class for %s\n", DEVNAME);
		return -1;
	}

	//create the device character file
	if(!device_create(gamepad_cls, NULL, devno, NULL, DEVNAME)) {
		printk(KERN_WARNING"Error while creating the device for %s\n", DEVNAME);
		return -1;
	}

	//Interrupt handling in the kernel
	request_irq(17, handler, 0, "EVEN", NULL);
	request_irq(18, handler, 0, "ODD", NULL);
	return 0;
}

/*
 * Handler to read the buttons whenever they change and save the value in the global
 * variable to allow it to be received by the user on read
 */
irqreturn_t handler(int irq, void *dev_id, struct pt_regs *regs){
	buttons_value = *GPIO_PC_DIN;
	*GPIO_IFC = *GPIO_IF;
	return IRQ_HANDLED;
}

/*
 * Function called while the device file is opened (nothing happens)
 */
static int gamepad_open(struct inode *inode, struct file *filp) {
	//printk(KERN_INFO"Device file has been opened\n");
	return 0;
}

/*
 * Function called while the device file is closed (nothing happens)
 */
static int gamepad_release(struct inode *inode, struct file *filp) {
	//printk(KERN_INFO"Device file has been closed\n");
	return 0;
}

/*
 * Function called while the device file is read.
 * The byte containing the buttons values is passed to the user and any successive reads give EOF
 */
static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	//buttons_value = *GPIO_PC_DIN; //TODO implement the interrupt to populate this (and remove this line)
	if(*offp >= 1) return 0; //EOF
	//printk(KERN_INFO"Buttons value is %x\n", buttons_value);
	if(copy_to_user(buff, &buttons_value, 1)) {
		printk(KERN_WARNING"Missing some bytes, failing\n");
		return -EFAULT;
	}
	*offp+=1; //1 byte read
	return 1;
}

/*
 * Function called while the device file is written to
 * Not really used, here just testing it's functionality by logging the received value
 */
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
	device_destroy(gamepad_cls, devno);
	class_destroy(gamepad_cls);
	cdev_del(&gamepad_cdev);
	unregister_chrdev_region(devno, DEVCNT);
	free_irq(17, NULL);
	free_irq(18, NULL);

}

module_init(gamepad_init);
module_exit(gamepad_cleanup);

MODULE_DESCRIPTION("Module to read the buttons value");
MODULE_LICENSE("GPL");

