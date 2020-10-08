#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to setup the timer 
 */
void setupTimer(uint16_t period)
{
	//Setup of timer, used by interupt solution
	
	//Enable clock on timer module
	*CMU_HFPERCLKEN0 |= 1 << 6;
	//Set the period of the timer. Fires interrupt and resets counter at period.
	*TIMER1_TOP = period;
	//Enable timer interrupt generation by timer module
	*TIMER1_IEN = 1;
	//Start the timer 
	*TIMER1_CMD = 1;

}
