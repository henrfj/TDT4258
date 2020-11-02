#include "player.h"

//arrays without including their length (unlike previous solution)
uint16_t periods[MAX_SONG];
uint8_t amplitudes[MAX_SONG];
uint8_t speeds[MAX_SONG];
uint8_t length = 0;

int play_song()
{
	static uint16_t i = 0;	//index of array in the song
	static uint16_t timer = 0;	//Return changing note counter
	uint8_t ret = GO_ON;


	uint16_t period = periods[i];
	uint8_t ampl = amplitudes[i];
	uint8_t speed = speeds[i];

	/*
		* the timer variable keeps track on how long the note has
		* been playing, since the board's timer is set to vibrate
		* with the note's frequency, the duration of timer depends
		* on it (defined with the GET_DURATION, more in the header)
		* in the beginning of a note, it's frequency is set to the
		* timer, so that the produced sound matches it. When the
		* expected duration has been reached, the next note is
		* selected or the playback is stopped if the song is over.
		*/
	if (timer == 1) {
		SET_PERIOD(period);	//set the new frequency on the timer
		get_set_amplitude(GET_AMPL(ampl));
	} else if (timer > GET_DURATION(period, speed)) {
		timer = 0;
		i++;
		if (i > length) {
			i = 0;
			length = 0; //restore the length for the next sound
			ret = STOP_HERE;
		}
	}

	timer++;
	/*
	* if the song is over, the return a different value to
	* stop the timer from the IRQ handler itself. That cannot
	* be done here as the interrupt request needs to be cleared
	* before (and that's done in the handler)
	*/
	return ret;
}

int get_set_amplitude(int mode)
{
	static int amp = BASE_AMPL;

	if (mode == NO_CHANGE) {
		return amp;
	}

	return amp = mode;
}

void push_values(uint16_t period, uint8_t ampl, uint8_t speed) {
	periods[length] = period;
	speeds[length] = speed;
	amplitudes[length] = ampl;
	length++;
}