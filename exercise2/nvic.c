#include "efm32gg.h"

/*
 * function to set up the interrupt generation of various modules
 */
void setupNVIC()
{

	//Enable timer module interrupt generation
	*ISER0 |= 1 << 12;

	//Enable GPIO A and C interrupt generation
	*ISER0 |= 0x802;

}
