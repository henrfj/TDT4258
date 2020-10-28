#include "player.h"

void play_sound(uint16_t period, uint8_t ampl, uint8_t speed) {
	uint8_t amplitude;
	unsigned int duration;
	unsigned int compond_timer;

	//get amplitude
	amplitude = GET_AMPL(ampl);	//amplitude is way too low

	//period is in usec
	//get duration. "1/speed" is no. 1/16 of a beat
	duration = GET_DURATION(period, speed);	//duration in num_periods

	//duration = (BEAT / speed); //duration in seconds (BEAT = seconds/beat)
	//clk_duration = duration * CPU_FREQ; // should be multiplied by CPU_FREQ

	compond_timer = 0;
	printk(KERN_WARNING"Duration is %d times (%d us)\n", duration, duration * period);
	while (compond_timer < duration) {
		play_period(amplitude, period);
		compond_timer++;
	}

}

/*
 * Single tick of a note, implementing the same square wave using
 * busy waiting
 */
void play_period(uint8_t amplitude, uint16_t period) {
	*DAC0_CH0DATA = amplitude;
	*DAC0_CH1DATA = amplitude;
	SLEEP(period / 2);
	*DAC0_CH0DATA = 0x000;
	*DAC0_CH1DATA = 0x000;
	SLEEP(period / 2);
}
