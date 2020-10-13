#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"

/*
 * TIMER1 interrupt handler 
 */
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	static uint8_t phase = 1;
	int amp = get_set_amplitude(NO_CHANGE);
	uint8_t status;

	/*
	 * Square wave produced by alternating two phases
	 * static variables are used to keep the value among calls
	 * the amplitude used is fetched by the library function
	 * After the two phases the library function to progress inside
	 * the tone is called, representing a tick in the song
	 * (more details follow)
	 */

	if (phase) {
		*DAC0_CH0DATA = amp;
		*DAC0_CH1DATA = amp;
	} else {
		*DAC0_CH0DATA = 0x000;
		*DAC0_CH1DATA = 0x000;
		status = play_song(NO_CHANGE);	//get next note after 2 phases
	}
	phase = !phase;		//invert it

	//Clear the interrupt 
	*TIMER1_IFC = 1;
	//if needed, pause after resetting
	if (status == STOP_HERE)
		PAUSE();
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{

	int button_value = *GPIO_PC_DIN;

	// Handler function (common to even and odd pins) is called
	read_button_value(button_value);

	*GPIO_IFC = *GPIO_IF;

}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	int button_value = *GPIO_PC_DIN;

	// Handler function (common to even and odd pins) is called
	read_button_value(button_value);

	*GPIO_IFC = *GPIO_IF;
}
