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
	printk(KERN_INFO"Setting up the DAC and timer to enable sound\n");
	//Make sure the DAC clock is prescaled correctly,
	//and enables the DAC output to the amplifier
	*DAC0_CTRL = 0x50010;
	//Enable the left and right DAC channels
	*DAC0_CH0CTRL = 1;
	*DAC0_CH1CTRL = 1;

	//Enable clock on timer module
	//*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER3;
	//Set the period of the timer. Fires interrupt and resets counter at period.
	*TIMER3_TOP = 0xfff;
	//Enable timer interrupt generation by timer module
	//*TIMER3_IEN = 1;
	//Start the timer 
	*TIMER3_CMD = 1;

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

	request_irq(19, handler, 0, "TIMER", NULL);

	PAUSE(); //will be started by userspace

	return 0;
}


irqreturn_t handler(int irq, void *dev_id, struct pt_regs *regs){
	static uint8_t phase = 1;
	int amp = get_set_amplitude(NO_CHANGE);
	uint8_t status;

	/*
	 * Square wave produced by alternating two phases
	 * static variables are used to keep the value among calls
	 * the amplitude used is fetched by the library function
	 * After the two phases the library function to progress inside
	 * the tone is called, representing a tick in the song
	 * (more details follow)
	 */

	if (phase) {
		*DAC0_CH0DATA = amp;
		*DAC0_CH1DATA = amp;
	} else {
		*DAC0_CH0DATA = 0x000;
		*DAC0_CH1DATA = 0x000;
		status = play_song();	//get next note after 2 phases
	}
	phase = !phase;		//invert it

	//Clear the interrupt 
	*TIMER3_IFC = 1;
	//if needed, pause after resetting
	if (status == STOP_HERE)
		PAUSE();
	return IRQ_HANDLED;
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
		push_values(period, ampl, speed);
	}
	PLAY();
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
	free_irq(19, NULL);

}

module_init(sound_init);
module_exit(sound_cleanup);

MODULE_DESCRIPTION("Sound driver...");
MODULE_LICENSE("GPL");

//---------------------------------------

//arrays without including their length (unlike previous solution)
uint16_t periods[MAX_SONG];
uint8_t amplitudes[MAX_SONG];
uint8_t speeds[MAX_SONG];
uint8_t length = 0;

int play_song()
{
	static uint16_t i = 0;	//index of array in the song
	static uint16_t timer = 0;	//Return changing note counter
	uint8_t ret = GO_ON;


	uint16_t period = periods[i];
	uint8_t ampl = amplitudes[i];
	uint8_t speed = speeds[i];

	if(length == 0) {
		return STOP_HERE;
	}

	/*
		* the timer variable keeps track on how long the note has
		* been playing, since the board's timer is set to vibrate
		* with the note's frequency, the duration of timer depends
		* on it (defined with the GET_DURATION, more in the header)
		* in the beginning of a note, it's frequency is set to the
		* timer, so that the produced sound matches it. When the
		* expected duration has been reached, the next note is
		* selected or the playback is stopped if the song is over.
		*/
	if (timer == 1) {
		SET_PERIOD(period);	//set the new frequency on the timer
		get_set_amplitude(GET_AMPL(ampl));
	} else if (timer > GET_DURATION(period, speed)) {
		timer = 0;
		i++;
		if (i > length) {
			i = 0;
			length = 0; //restore the length for the next sound
			ret = STOP_HERE;
		}
	}

	timer++;
	/*
	* if the song is over, the return a different value to
	* stop the timer from the IRQ handler itself. That cannot
	* be done here as the interrupt request needs to be cleared
	* before (and that's done in the handler)
	*/
	return ret;
}

int get_set_amplitude(int mode)
{
	static int amp = BASE_AMPL;

	if (mode == NO_CHANGE)
		return amp;

	return amp = mode;
}

void push_values(uint16_t period, uint8_t ampl, uint8_t speed) {
	periods[length] = period;
	speeds[length] = speed;
	amplitudes[length] = ampl;
	length++;
}
