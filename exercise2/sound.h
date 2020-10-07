#ifndef SOUND_H_
#define SOUND_H_

#include "efm32gg.h"

//modes for play_song() function
#define NO_CHANGE -1
#define NEW_TONE(id) id

//return values for the play_song() function
#define GO_ON 0
#define STOP_HERE 1

#define LEFT    (0xfe)
#define RIGHT   (0xbf)
#define LEFTR   (0xef)
#define RIGHTL  (0xfb)
#define UPL     (0xfd)
#define UPR     (0xdf)
#define DOWNL   (0xf7)
#define DOWNR   (0x7f)

#define CPU_FREQ 14000000
#define BEAT 0.35		//value approximately in seconds for a standard note

/*
 * helper macros to make use of the frequency value stored in the
 * songs. The period is the number set to the timer, while the
 * duration is the actual time in seconds each note lasts. The number
 * changes with the frequency as the returned value is actually the
 * number of full square waves (ticks) played. It can be scaled by the
 * speed factor depending on the song
 */
#define GET_PERIOD(freq) ((uint16_t)(CPU_FREQ / (freq*2)))
#define SET_FREQ(freq) (*TIMER1_TOP = GET_PERIOD(freq))
#define GET_DURATION(freq, speed) ((uint32_t)(BEAT*freq/speed))

// Set the bit in the clock register to enable-disable the timer
#define PLAY() (*CMU_HFPERCLKEN0 |= (1 << 6))
#define PAUSE() (*CMU_HFPERCLKEN0 &= ~(1 << 6))

#define BASE_AMPL 0x1f
#define GET_AMPL(level) (BASE_AMPL+(level<<1))

int get_set_amplitude(int mode);

int play_song(int mode);

void read_button_value(int button_value);

//POLLING UNDER HERE

void polling_solution();

void polling_one_period(uint8_t amplitude, float period);

void polling_play_sound(int current_song_id);

void test_timer();

void my_sleep_1(float secs);

void my_sleep_2(float secs);

#endif
