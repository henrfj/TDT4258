        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  	// The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset: 
		

		/////////////////////////////////////////////////////////////////////////////
		// General setup for LEDS and BUTTONS
		////////////////////////////////////////////////////////////////////////////
	

		//Activate clk on GPIO_CONTROLLER
	    ldr r1, =CMU_BASE
		ldr r2, [r1, #CMU_HFPERCLKEN0] 	// loads HFPERCLK ENABLE value

		mov r3, #1
		lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
		orr r2, r2, r3					// prepares value with gpio clock bit set to 1

		str r2, [r1, #CMU_HFPERCLKEN0]  // stores GPIO activate bit.

		//Set high drive for LEDS (Port A)
		ldr r5, =GPIO_PA_BASE
		mov r2, #0x2
		str r2, [r5, #GPIO_CTRL]

		//Setting output pins for LEDS (Port A)
		mov r2, #0x55555555
		str r2, [r5, #GPIO_MODEH]

		//Setting input pins for BUTTONS (PORT C)
		ldr r3, =GPIO_PC_BASE
		mov r4, #0x33333333
		str r4, [r3, #GPIO_MODEL]

		//Setting internal pull-ups for BUTTONS (Port C)
		mov r4, #0xFF
		str r4, [r3, #GPIO_DOUT]


		/////////////////////////////////////////////////////////////////////////////
		//
		// Pooling specific infinite loop
		// The program will runn this part infinitly after setup
		//
		////////////////////////////////////////////////////////////////////////////

		loop:

			// Loading button status onto r4
			ldr r4, [r3, #GPIO_DIN]

			// Left shifting the input, to mach the required input of leds
			lsl r4, r4, #8
			str r4, [r1, #GPIO_DOUT]

			b loop


        .thumb_func
gpio_handler:  

	      b .  // do nothing
	

	
        .thumb_func
dummy_handler:  
        b .  // do nothing

