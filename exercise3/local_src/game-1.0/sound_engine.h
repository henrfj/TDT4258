#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

//get period in ms out of frequency in Hz
#define GET_PERIOD(freq) ((uint16_t)(1.0e6 / (freq)))
#define DEVFILE "/dev/sound_ctrl"

//buf must be 32 bits, first half is period then 8 bits ampl and 8 spd
#define MKPACK(t, ampl, spd) ((t<<16) | (ampl<<8) | spd)

#define PLAY_DAMAGE()      play_song(0) //block
#define PLAY_SCORE()       play_song(1) //coin
#define PLAY_BACKGROUND()  play_song(3) //gym
#define PLAY_MENU()        play_song(5) //rescue

void play_single_sound(uint16_t period, uint8_t ampl, uint8_t speed);
void play_song(uint8_t songnum);

#endif
