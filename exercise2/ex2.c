#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"

/*
 * The period between sound samples, in clock cycles 
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
	//Setup for DAC, common for both Polling and IR solution        
	setupDAC();

#ifdef POLLING
	//Setup for polling; turn on clk for GPIO, set button pins.
	setupGPIO();
	//Polling 
	polling_solution();

#else
	/*
	 * Enable interrupt handling and required hardware
	 */
	setupGPIO();
	setupTimer(SAMPLE_PERIOD);
	//Set up GPIO related registers to generate requests
	setupGPIOirq();
	setupNVIC();

	/*
	 * Entering sleep mode while waiting for interrupt and returning to
	 * sleep mode while exiting IRQ handler, this is necessary to save
	 * energy compared to a busy-wait solution.
	 * Done by writing 0x6 to SCR.
	 *
	 * Cannot use deep sleep due to clk turned off?
	 * (here setting sleep instead of deep sleep)
	 */
	*SCR = 0x2;
	//__asm__("wfi");
	//while (1);

#endif

	return 0;
}

void setupNVIC()
{

	//Enable timer module interrupts
	*ISER0 |= 1 << 12;

	//Enable GPIO A and C
	*ISER0 |= 0x802;

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
