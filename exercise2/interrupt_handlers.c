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
		int period = get_period(NO_CHANGE); //1 is the sound-mode
		int frequency = get_counter(1) % period;
		int amp = get_set_amplitude(NO_CHANGE);

		//Square wave

		if (frequency >= (period/2)){
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


	//TODO: Turn of clock could save power, look into later
	//*CMU_HFPERCLKEN0 &= ~(1 << 6);

	int button_value = *GPIO_PC_DIN;

	read_button_value(button_value);

	*GPIO_IFC = *GPIO_IF;

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

	int button_value = *GPIO_PC_DIN;

	read_button_value(button_value);

	*GPIO_IFC = *GPIO_IF;
}


