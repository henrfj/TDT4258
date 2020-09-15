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

		//Activate clk on GPIO_CONTROLLER
	    ldr r1, =CMU_BASE
		ldr r2, [r1, #CMU_HFPERCLKEN0] 	// loads HFPERCLK ENABLE value
		
		mov r3, #1
		lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
		orr r2, r2, r3					// prepares value with gpio clock bit set to 1

		str r2, [r1, #CMU_HFPERCLKEN0]  // stores GPIO activate bit.

		//Set high drive strength (A)
		ldr r1, =GPIO_PA_BASE
		mov r2, #0x2
		str r2, [r1, #GPIO_CTRL]

		//Setting pins as output (A)
		mov r2, #0x55555555
		str r2, [r1, #GPIO_MODEH]
		
		//Turn all on (pin 8-15)
		//For now we overwrite pin 0-7 with 00, might want to change that later.
		mov r2, #0xFF00
		str r2, [r1, #GPIO_DOUT]

		// Setting pins to low, test
		mov r2, #0x8C00
		str r2, [r1, #GPIO_DOUT]


		// BUTTONS pins set as input
		ldr r3, =GPIO_PC_BASE
		mov r4, #0x33333333
		str r4, [r3, #GPIO_MODEL]

		//Setting internal pull-ups
		mov r4, #0xFF
		str r4, [r3, #GPIO_DOUT]

		mov r6, #0x18 //initial value for change_leds
		loop: // POLLING
			bl change_leds
			b loop

// r1 is set as the output base while r3 is the input base
// r2 and r4 are used as temporary, hence they are not restored
// register r6 is kept as the value
LEFT  = 0x44
RIGHT = 0x11
UP    = 0x22
DOWN  = 0x88
change_leds:
			// Loading button status onto r4
			ldr r4, [r3, #GPIO_DIN]

			//left rotate (n<<7 & 0xff) | n>>1
			ldr r0, =LEFT
			//d=a & !b and update the status register (used for ne)
			bics r0, r0, r4
			ittt ne //if then block
			lsrne r2, r6, #7
			andne r2, r2, #0xff
			orrne r6, r2, r6, lsl #1 //shifts the second operand!

			//right rotate (n>>7 & 0xff) | n<<1
			ldr r0, =RIGHT
			bics r0, r0, r4
			ittt ne
			lslne r2, r6, #7
			andne r2, r2, #0xff
			orrne r6, r2, r6, lsr #1

			//remove rightmost (n & (n - 1))
			ldr r0, =DOWN
			bics r0, r0, r4
			itt ne
			subne r2, r6, #1
			andne r6, r2, r6

			//add leftmost (n | (n << 1)) & 0xff
			ldr r0, =UP
			bics r0, r0, r4
			itt ne
			orrne r6, r6, r6, lsl #1
			andne r6, r6, #0xff

			cmp r6, #0
			it eq
			moveq r6, #1

			//left shifting and negating the input, to match the required input of leds
			mvn r4, r6, lsl #8
			str r4, [r1, #GPIO_DOUT]

			mov r15, r14 //return

	
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  

	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

