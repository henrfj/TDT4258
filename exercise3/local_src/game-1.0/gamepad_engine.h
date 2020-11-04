#ifndef GAMEPAD_ENGINE_H
#define GAMEPAD_ENGINE_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define LEFT    (0xfe)
#define RIGHT   (0xbf)
#define LEFTR   (0xef)
#define RIGHTL  (0xfb)
#define UPL     (0xfd)
#define UPR     (0xdf)
#define DOWNL   (0xf7)
#define DOWNR   (0x7f)

char read_button_value();



#endif