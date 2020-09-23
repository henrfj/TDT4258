#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"

/*
 * TIMER1 interrupt handler 
 */
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */

		// TODO: Change 2 for different frequency
		int trigger = get_counter(1) % 2;	
		int amp = get_set_amplitude(NO_CHANGE);

		if (trigger==1){
			//12-bit registers, dont forget
			*DAC0_CH0DATA = amp;
			*DAC0_CH1DATA = amp;
		}else{
			*DAC0_CH0DATA = 0x000;
			*DAC0_CH1DATA = 0x000;
		}

	//Clear the interrupt 
	*TIMER1_IFC = 1;
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}
