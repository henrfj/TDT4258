#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"

/*
 * The period between sound samples, given in clock cycles 
 * This is the initial setup, will be changed later based on
 * the required note to be played
 */
#define   SAMPLE_PERIOD   10000

/*
 * Declaration of peripheral setup functions 
 */
void setupDAC();
//IR-specific setups
void setupGPIO();
void setupTimer(uint32_t period);
void setupNVIC();
//Polling setup
void setupGPIOirq();

int main(void)
{
	//Setup common for both Polling and IR solution 
	//CLK on DAC       
	setupDAC();
	//Clk for GPIO, set button pins as input.
	setupGPIO();

#ifdef POLLING
	//Polling 
	polling_solution();

#else
	/*
	 * Additional setup needed for interrupt-solution.
	 * Enable interrupt handling and required hardware
	 */
	//setting up timer with an arbritary initial period.
	setupTimer(SAMPLE_PERIOD);
	//Set up GPIO related registers to generate ir-requests
	setupGPIOirq();
	//Turn on interrupt handling in the processor
	setupNVIC();

	/*
	 * Entering sleep mode while waiting for interrupt and returning to
	 * sleep mode while exiting IRQ handler, this is necessary to save
	 * energy compared to a busy-wait solution.
	 * Done by writing 0x2 to SCR.
	 *
	 * Cannot use deep sleep due to high frequency clk 
	 * being turned off => The timer cannot send ir-requests.
	 */
	*SCR = 0x2;

#endif

	return 0;
}
