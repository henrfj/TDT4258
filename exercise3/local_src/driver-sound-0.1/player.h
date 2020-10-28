/**
 * @author      : Gabriele Monaco (glemco@fedora-pc)
 * @file        : player
 * @created     : Sunday Oct 25, 2020 08:57:43 CET
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include <linux/types.h>
#include <linux/delay.h>

#define BEAT 350000  //value approximately in usec for a standard beat

#define BASE_AMPL 0x1f
#define GET_AMPL(level) (BASE_AMPL+(level<<1))
#define GET_DURATION(period, speed) ((BEAT / speed) / period)

#define SLEEP(usec) usleep_range(usec, usec)

void play_sound(uint16_t period, uint8_t ampl, uint8_t speed);
void play_period(uint8_t amplitude, uint16_t period);

#endif // _PLAYER_H

