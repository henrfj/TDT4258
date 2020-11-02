#ifndef _DRIVER_SOUND_H
#define _DRIVER_SOUND_H

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include "efm32gg.h"

#define DEVNAME "sound_ctrl"
#define DEVCNT 4
#define MAXBUF 50

//Get a string from the variable name
#define MODENAME(mode) #mode
#define MODE_NOTE 0
#define MODE_AMPL 1
#define MODE_SPD  2
#define MODE_TRIG 3

typedef struct {
	char ready;
	struct cdev sound_cdev;
} sound_dev;

/*Timer interrupt handler to play a period*/
irqreturn_t handler(int irq, void *dev_id, struct pt_regs *regs);
/* user program opens the driver */
static int sound_open(struct inode *inode, struct file *filp);
/* user program closes the driver */
static int sound_release(struct inode *inode, struct file *filp);
/* user program reads from the driver */
static ssize_t sound_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
/* user program writes to the driver */
static ssize_t sound_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);



#endif // _DRIVER_SOUND_H
