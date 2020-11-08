#ifndef GAMEPAD_ENGINE_H
#define GAMEPAD_ENGINE_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>


#define INV(b)  ((~b) & 0xff)
#define LEFT    INV(0xfe)
#define RIGHT   INV(0xbf)
#define LEFTR   INV(0xef)
#define RIGHTL  INV(0xfb)
#define UPL     INV(0xfd)
#define UPR     INV(0xdf)
#define DOWNL   INV(0xf7)
#define DOWNR   INV(0x7f)

//check like CHECK_BTN(button_value, LEFT)
#define CHECK_BTN(btn, dir) (INV(btn) & dir)

char read_button_value();
void gamepad_test();



#endif
