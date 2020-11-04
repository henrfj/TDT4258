
#ifndef _PLAYER_H
#define _PLAYER_H

#include <linux/types.h>
#include "efm32gg.h"

//modes for play_song() function
#define NO_CHANGE -1

//return values for the play_song() function
#define GO_ON 0
#define STOP_HERE 1

#define CPU_FREQ 14 //Megaherz
#define BEAT 350000	//value approximately in microseconds for a standard beat

/*
 * helper macros to make use of the frequency value stored in the
 * songs. The period is the number set to the timer, while the
 * duration is the actual time in seconds each note lasts. The number
 * changes with the frequency as the returned value is actually the
 * number of full square waves (ticks) played. It can be scaled by the
 * speed factor depending on the song
 */
#define GET_CONST(period) ((uint16_t)(CPU_FREQ * (period/2)))
#define SET_PERIOD(period) (*TIMER3_TOP = GET_CONST(period))
#define GET_DURATION(period, speed) (BEAT / (speed * period))

// Set the bit in the clock register to enable-disable the timer
#define PLAY() (*TIMER3_IEN = 1)
#define PAUSE() (*TIMER3_IEN = 0)

#define BASE_AMPL 0x1f
#define GET_AMPL(level) (BASE_AMPL+(level<<1))

#define MAX_SONG 740

//////////////////////////////
//    INTERRUPT  SOLUTION   //
//////////////////////////////

int play_song();

int get_set_amplitude(int mode);

void push_values(uint16_t period, uint8_t ampl, uint8_t speed);

#endif // _PLAYER_H

