#ifndef SOUND_H_
#define SOUND_H_


#include "efm32gg.h"

#define NO_CHANGE -1
#define LEFT    ((~0x40) & 0xff)
#define RIGHT   ((~0x01) & 0xff)
#define CENTER  ((~0x14) & 0xff) //actually LEFTR | RIGHTL
#define UPL     ((~0x20) & 0xff)
#define UPR     ((~0x02) & 0xff)
#define DOWNL   ((~0x80) & 0xff)
#define DOWNR   ((~0x08) & 0xff)



int get_counter(int increase);
int get_set_amplitude(int mode);

int get_period(int mode);

void read_button_value(int button_value);







#endif



