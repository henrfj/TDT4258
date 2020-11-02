#ifndef _GAMEPAD_H
#define _GAMEPAD_H

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include "efm32gg.h"

#define DEVNAME "gamepad"
#define DEVCNT 1

/*Interrupt handler for gamepad interrupts*/
irqreturn_t handler(int irq, void *dev_id, struct pt_regs *regs);
/* user program opens the driver */
static int gamepad_open(struct inode *inode, struct file *filp);
/* user program closes the driver */
static int gamepad_release(struct inode *inode, struct file *filp);
/* user program reads from the driver */
static ssize_t gamepad_read(struct file *filp, char __user *buff, size_t count, loff_t *offp);
/* user program writes to the driver */
static ssize_t gamepad_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp);



#endif // _GAMEPAD_H
