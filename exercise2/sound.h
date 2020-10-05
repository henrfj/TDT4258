#ifndef SOUND_H_
#define SOUND_H_


#include "efm32gg.h"

#define NO_CHANGE -1
#define NEW_TONE(id) id

#define LEFT    (0xfe)
#define RIGHT   (0xbf)
#define LEFTR   (0xef)
#define RIGHTL  (0xfb)
#define UPL     (0xfd)
#define UPR     (0xdf)
#define DOWNL   (0xf7)
#define DOWNR   (0x7f)

#define CPU_FREQ 14000000
#define NOTE_DURATION 0.25

#define GET_PERIOD(freq) ((uint16_t)(CPU_FREQ / (freq*2)))
#define SET_FREQ(freq) (*TIMER1_TOP = GET_PERIOD(freq))
#define GET_DURATION(freq, speed) ((uint32_t)(NOTE_DURATION*freq/speed))

#define PLAY() (*CMU_HFPERCLKEN0 |= (1 << 6))
#define PAUSE() (*CMU_HFPERCLKEN0 &= ~(1 << 6))

#define GO_ON 0
#define STOP_HERE 1

#define BASE_AMPL 0x5f
#define GET_AMPL(level) (BASE_AMPL+(level<<2))


int get_set_amplitude(int mode);

int play_song(int mode);

void read_button_value(int button_value);







#endif



