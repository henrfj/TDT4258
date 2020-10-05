#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "efm32gg.h"
#include <stdio.h>

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
void setupGPIO();
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void polling_testing();
void polling_solution();


/*
 * Your code will start executing here 
 */
#define POLLING //FIXME define it in a custom target in the Makefile
int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	
	setupDAC();
	setupTimer(SAMPLE_PERIOD);
	setupGPIO();
	

	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */


	// Testing polling of timer value using LEDs. 
	// Polling version of the DAC control, reading from the timer
#ifdef POLLING
	polling_solution();
#else
	/*
	 * Enable interrupt handling 
	 */
	setupNVIC();
	while(1){

	}
#endif

	return 0;
}

void polling_solution(){
    uint8_t playing = 0;
	int button_value = *GPIO_PC_DIN;
	int prev_button_value = *GPIO_PC_DIN;
    while(1){
        if(playing){
			while(!get_set_song_done(GET_DONE, 0)){ 
				static uint8_t phase = 1;
				int amp = get_set_amplitude(NO_CHANGE);
				uint8_t status;
				//Square wave
				if (phase){
					//12-bit registers, dont forget
					*DAC0_CH0DATA = amp;
					*DAC0_CH1DATA = amp;
				} else {
					*DAC0_CH0DATA = 0x000;
					*DAC0_CH1DATA = 0x000;
					//get next note after 2 phases
					status = play_song(NO_CHANGE); 
				}
				phase = !phase; //invert it

				Sleep(0.04);
				/*
				while(*TIMER1_CNT >= *TIMER1_TOP){	

				}
				*TIMER1_CNT = 0;
				*/

			}
			get_set_song_done(SET_DONE, 0);
			prev_button_value = button_value;
			playing = 0;

        }else if(button_value != prev_button_value){
            read_button_value(button_value);
			playing = 1;

        }else{
			button_value = *GPIO_PC_DIN;
		}

    }

}

void polling_testing(){
		int x = 0;
		volatile uint32_t* test = TIMER1_CNT;
		if (*test < SAMPLE_PERIOD/2){
			x = 1;
		}
		if (*test > SAMPLE_PERIOD/2){
			x = 0;
		}

		if (x==1){
			//*GPIO_PA_DOUT = 0x0000;
			*DAC0_CH0DATA = 0x005;
			*DAC0_CH1DATA = 0x005;
		}else{
			//*GPIO_PA_DOUT = 0xff00;
			*DAC0_CH0DATA = 0x000;
			*DAC0_CH1DATA = 0x000;
		}

		//*GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;	
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
