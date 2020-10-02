#ifndef SOUND_H_
#define SOUND_H_


#include "efm32gg.h"

#define NO_CHANGE -1
#define NEW_TONE(id) id

#define LEFT    ((~0x40) & 0xff)
#define RIGHT   ((~0x01) & 0xff)
#define LEFTR   ((~0x04) & 0xff)
#define RIGHTL  ((~0x10) & 0xff)
#define UPL     ((~0x20) & 0xff)
#define UPR     ((~0x02) & 0xff)
#define DOWNL   ((~0x80) & 0xff)
#define DOWNR   ((~0x08) & 0xff)

#define CPU_FREQ 14000000
#define NOTE_DURATION 0.2

#define GET_PERIOD(freq) ((uint16_t)(CPU_FREQ / (freq*2)))
#define SET_FREQ(freq) (*TIMER1_TOP = GET_PERIOD(freq))
#define GET_DURATION(freq) ((uint32_t)(NOTE_DURATION*freq))

#define PLAY() (*CMU_HFPERCLKEN0 |= (1 << 6))
#define PAUSE() (*CMU_HFPERCLKEN0 &= ~(1 << 6))

#define BASE_AMPL 0x5f
#define GET_AMPL(level) (BASE_AMPL+(level<<2))


int get_set_amplitude(int mode);

int play_song(int mode);

void read_button_value(int button_value);







#endif



