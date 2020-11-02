/**
 * @author      : Gabriele Monaco (glemco@fedora-pc)
 * @file        : main
 * @created     : Sunday Oct 25, 2020 13:30:33 CET
 */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>


#include "songs.h"

//get period in ms out of frequency in Hz
#define GET_PERIOD(freq) ((uint16_t)(1.0e6 / (freq)))
#define DEVFILE "/dev/sound_ctrl"

//buf must be 32 bits, first half is period then 8 bits ampl and 8 spd
#define MKPACK(t, ampl, spd) ((t<<16) | (ampl<<8) | spd)

void play_single_sound(uint16_t period, uint8_t ampl, uint8_t speed) {
	FILE *devfile = fopen(DEVFILE, "w");
	uint32_t buf;
	if(!devfile) {
		fprintf(stderr, "Could not open device file\n");
		exit(1);
	}
	buf = MKPACK(period, ampl, speed);
	fwrite(&buf, sizeof(uint32_t), 1, devfile);
	fclose(devfile);
}

// void play_song_test(uint8_t songnum) {

// 	/*
// 	 * Get all songs parameters from the header and plug them in the driver
// 	 * use the play_single_sound each time (slower) and profile each run
// 	 */

// 	struct timespec start, end;
// 	uint16_t period;
// 	uint8_t ampl;
// 	uint8_t speed;

// 	//the length of the array is saved in its first element
// 	int len = SONG(songnum)[0];
// 	int i;
// 	for(i=1; i<=len; i++) {
// 		period = GET_PERIOD(SONG(songnum)[i]);
// 		ampl = SONG_AMPL(songnum)[i];
// 		speed = SONG_SPD(songnum)[i];
// 		printf("Playing (%d, %d, %d)\n", period, ampl, speed);
// 		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
// 		play_single_sound(period, ampl, speed);
// 		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
// 		float delta = (end.tv_sec-start.tv_sec)*1e3 +
// 			(end.tv_nsec-start.tv_nsec)/1.e6;
// 		printf("This note lasted %.3f ms\n", delta);
// 	}
// 	return;
// }



#define BUFSIZE 100
void play_song(uint8_t songnum) {

	FILE *devfile = fopen(DEVFILE, "w");
	/*
	 * Get all songs parameters from the header and plug them in the driver
	 */

	uint16_t period;
	uint8_t ampl;
	uint8_t speed;
	uint32_t buf[BUFSIZE];

	//the length of the array is saved in its first element
	int len = SONG(songnum)[0];
	int i;
	for(i=1; i<=len; i++) {
		period = GET_PERIOD(SONG(songnum)[i]);
		ampl = SONG_AMPL(songnum)[i];
		speed = SONG_SPD(songnum)[i];
		buf[i-1] = MKPACK(period, ampl, speed);
	}
	fwrite(&buf, sizeof(uint32_t), len, devfile);
	fclose(devfile);
	return;

}
int main() {
	//play_song_test(0);
	play_song(2);
    return 0;
}

