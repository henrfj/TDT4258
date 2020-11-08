#include "sound_engine.h"
#include "songs.h"

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
	for(i=1; i<=len && i<BUFSIZE; i++) {
		period = GET_PERIOD(SONG(songnum)[i]);
		ampl = SONG_AMPL(songnum)[i];
		speed = SONG_SPD(songnum)[i];
		buf[i-1] = MKPACK(period, ampl, speed);
	}
	fwrite(&buf, sizeof(uint32_t), len, devfile);
	fclose(devfile);
	return;

}
