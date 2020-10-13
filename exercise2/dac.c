#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setupDAC()
{

	//Enable the DAC clock
	*CMU_HFPERCLKEN0 |= 1 << 17;
	//Make sure the DAC clock is prescaled correctly,
	//and enables the DAC output to the amplifier
	*DAC0_CTRL = 0x50010;
	//Enable the left and right DAC channels
	*DAC0_CH0CTRL = 1;
	*DAC0_CH1CTRL = 1;

}
