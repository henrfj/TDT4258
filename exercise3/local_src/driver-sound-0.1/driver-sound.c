/*
 * Sound driver
 */

#include "driver-sound.h"
#include "player.h"

/* Global attributes */
struct class *sound_cls;
dev_t devno;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = sound_read,
	.write = sound_write,
	.open = sound_open,
	.release = sound_release
};

sound_dev dev = {0};

static char *sound_devnode(struct device *dev, umode_t *mode) {
	if(mode) *mode = 0666; //a-rw mode
	return NULL;
}

/*
 * sound_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init sound_init(void)
{
	int err;
	printk(KERN_INFO"Setting up the DAC to enable sound\n");
	//Make sure the DAC clock is prescaled correctly,
	//and enables the DAC output to the amplifier
	*DAC0_CTRL = 0x50010;
	//Enable the left and right DAC channels
	*DAC0_CH0CTRL = 1;
	*DAC0_CH1CTRL = 1;

	//character device allocations
	err	= alloc_chrdev_region(&devno, 0, DEVCNT, DEVNAME);
	if(err<0) {
		printk(KERN_WARNING"Error while allocating the device (%d)\n", err);
		return err;
	}
	cdev_init(&dev.sound_cdev, &fops);
	dev.sound_cdev.owner = THIS_MODULE;
	dev.sound_cdev.ops = &fops;
	err = cdev_add(&dev.sound_cdev, devno, 1);
	if(err<0) {
		printk(KERN_WARNING"Error while adding the char device %s (%d)\n", DEVNAME, err);
	}

	sound_cls = class_create(THIS_MODULE, DEVNAME);
	if(!sound_cls) {
		printk(KERN_WARNING"Error while creating the device class for %s\n", DEVNAME);
		return -1;
	}
	sound_cls->devnode = sound_devnode;

	if(!device_create(sound_cls, NULL, devno, NULL, DEVNAME)) {
		printk(KERN_WARNING"Error while creating the device for %s\n", DEVNAME);
		return -1;
	}


	return 0;
}


static int sound_open(struct inode *inode, struct file *filp) {
	printk(KERN_INFO"Device file has been opened\n");
	return 0;
}

static int sound_release(struct inode *inode, struct file *filp) {
	printk(KERN_INFO"Device file has been closed\n");
	return 0;
}

#define READ_SIZE 3
static ssize_t sound_read(struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	char val[READ_SIZE] = "0\n";
	printk(KERN_INFO"Ready value is %d\n", dev.ready);
	val[0] = dev.ready + '0';
	if(*offp >= READ_SIZE) return 0; //EOF
	if(copy_to_user(buff, val, READ_SIZE)) {
		printk(KERN_WARNING"Missing some bytes, failing\n");
		return -EFAULT;
	}
	*offp += READ_SIZE;
	return READ_SIZE;
}

//buf must be 32 bits, first half is period then 8 bits ampl and 8 spd
#define BUFSIZE 100
#define UNPACK(buf,t,ampl,spd) *t=buf>>16; *ampl=(buf>>8)&0xff; *spd=buf&0xff
static ssize_t sound_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
	uint32_t numpacks, i;
	uint32_t val[BUFSIZE];
	uint16_t period;
	uint8_t ampl, speed;
	if(copy_from_user(val, buff, count)) {
		printk(KERN_WARNING"Missing some bytes, failing\n");
		return -EFAULT;
	}
	numpacks = count / 4; //4 bytes per packet
	printk("Got %d tones\n", numpacks);
	for(i=0; i<numpacks; i++) {
		UNPACK(val[i], &period, &ampl, &speed);
		printk(KERN_INFO"Written value is %x, (%d, %d, %d)\n", val[i], period, ampl, speed);
		play_sound(period, ampl, speed);
	}
	return count; //never EOF
}

/*
 * sound_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit sound_cleanup(void)
{
	 printk(KERN_INFO"Cleaning up the devices\n");
	 device_destroy(sound_cls, devno);
	 class_destroy(sound_cls);
	 cdev_del(&dev.sound_cdev);
	 unregister_chrdev_region(devno, DEVCNT);
}

module_init(sound_init);
module_exit(sound_cleanup);

MODULE_DESCRIPTION("Sound driver...");
MODULE_LICENSE("GPL");

