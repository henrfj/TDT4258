#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"

//Smooth frequency, found on yuotube
#define SMOOTH_F 26515
/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
/*
 * The period between sound samples, in clock cycles 
 */
#define   SAMPLE_PERIOD   10000

#define Tuner_frequency 5

/*
 * Declaration of peripheral setup functions 
 */
void setupDAC();
//IR-specific setups
void setupGPIO();
void setupTimer(uint32_t period);
void setupNVIC();
//Polling setup
void setupPolling();

int main(void)
{
	//Setup for DAC, common for both Polling and IR solution	
	setupDAC();

#ifdef POLLING
	//Setup for polling; turn on clk for GPIO/Timer, set button pins.
	//TODO: clean up setup files, putting all ir in one setup func.
	setupPolling();
	//Polling 
	polling_solution();
	//Timer tester
	//test_timer();



#else
	/*
	 * Enable interrupt handling 
	 */
	setupGPIO();
	setupTimer(SAMPLE_PERIOD);
	setupNVIC();
	
	/*
	Entering sleep mode while waiting for interrupt, 
	and returning to sleep mode while exiting IH is necessary to save energy
	compared to a busy-wait solution. Done by writing 0x6 to SCR.
	*/
	*SCR = 0x2; 	
	//__asm__("wfi");
	//while (1);
	

#endif

	return 0;
}



void setupNVIC()
{
	/*
	 * TODO use the NVIC ISERx registers to enable handling of
	 * interrupt(s) remember two things are necessary for interrupt
	 * handling: - the peripheral must generate an interrupt signal - the
	 * NVIC must be configured to make the CPU handle the signal You will
	 * need TIMER1, GPIO odd and GPIO even interrupt handling for this
	 * assignment. 
	 */

	//Enable timer module interrupts
	*ISER0 |= 1 << 12;

	//Enable GPIO A and C
	*ISER0 |=0x802;

}


void setupPolling(){
	//Enable GPIO clock 
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	
	//BUTTONS
	*GPIO_PC_MODEL = 0x33333333; /*Setting pins as input pins */
	*GPIO_PC_DOUT = 0xff;	/*Internal pull-ip resistors for the buttons*/
}

/*
 * if other interrupt handlers are needed, use the following names:
 * NMI_Handler HardFault_Handler MemManage_Handler BusFault_Handler
 * UsageFault_Handler Reserved7_Handler Reserved8_Handler
 * Reserved9_Handler Reserved10_Handler SVC_Handler DebugMon_Handler
 * Reserved13_Handler PendSV_Handler SysTick_Handler DMA_IRQHandler
 * GPIO_EVEN_IRQHandler TIMER0_IRQHandler USART0_RX_IRQHandler
 * USART0_TX_IRQHandler USB_IRQHandler ACMP0_IRQHandler ADC0_IRQHandler
 * DAC0_IRQHandler I2C0_IRQHandler I2C1_IRQHandler GPIO_ODD_IRQHandler
 * TIMER1_IRQHandler TIMER2_IRQHandler TIMER3_IRQHandler
 * USART1_RX_IRQHandler USART1_TX_IRQHandler LESENSE_IRQHandler
 * USART2_RX_IRQHandler USART2_TX_IRQHandler UART0_RX_IRQHandler
 * UART0_TX_IRQHandler UART1_RX_IRQHandler UART1_TX_IRQHandler
 * LEUART0_IRQHandler LEUART1_IRQHandler LETIMER0_IRQHandler
 * PCNT0_IRQHandler PCNT1_IRQHandler PCNT2_IRQHandler RTC_IRQHandler
 * BURTC_IRQHandler CMU_IRQHandler VCMP_IRQHandler LCD_IRQHandler
 * MSC_IRQHandler AES_IRQHandler EBI_IRQHandler EMU_IRQHandler 
 */


