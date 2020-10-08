#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to set up GPIO mode and interrupts
 */
void setupGPIO()
{

	//Enable GPIO clock
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	

	//BUTTONS
	*GPIO_PC_MODEL = 0x33333333;	/*Setting pins as input pins */
	*GPIO_PC_DOUT = 0xff;	/*Internal pull-ip resistors for the buttons */


	/* LED
	 * Not used in this exercise, commented out to save power
	 * *GPIO_PA_CTRL = 2;   // set high drive stre
	 * *GPIO_PA_MODEH = 0x55555555; // set pins A8-15 as ou
	 * *GPIO_PA_DOUT = 0xff00;       // turn on LEDs D4-D8 (LEDs are active low) 
	*/

}

void setupGPIOirq()
{
	//Interrupt handling GPIO

	//Setting BUTTON port to allow interrupts (Port C)
	*GPIO_EXTIPSELL = 0x22222222;

	//Enables interrupts on rise and fall values, and interrupt generation
	// from the GPIO
	*GPIO_IEN = 0xff;	//enable generation
	*GPIO_EXTIRISE = 0xff;	//enable generation on rise
	*GPIO_EXTIFALL = 0xff;	//enable generation on fall
}
