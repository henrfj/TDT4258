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
		// All setup required for using leds and buttons.


		//Activate clk on GPIO_CONTROLLER
	    ldr r1, =CMU_BASE //
		ldr r2, [r1, #CMU_HFPERCLKEN0]

		mov r3, #1
		lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
		orr r2, r2, r3

		str r2, [r1, #CMU_HFPERCLKEN0]

		
		//Set high drive strength (A)
		ldr r5, =GPIO_PA_BASE
		mov r2, #0x2
		str r2, [r5, #GPIO_CTRL]

		//Setting pins as output (A)
		mov r2, #0x55555555
		str r2, [r5, #GPIO_MODEH]

		// BUTTONS pins set as input
		ldr r3, =GPIO_PC_BASE
		mov r4, #0x33333333
		str r4, [r3, #GPIO_MODEL]

		//Setting internal pull-ups for buttons
		mov r4, #0xFF
		str r4, [r3, #GPIO_DOUT]

		
		//Sets what ports are allowed to interrupt (Buttons)
		ldr r1, =GPIO_BASE
		mov r2, #0x22222222
		str r2, [r1, #GPIO_EXTIPSELL]

		//Enables interrupts on rise and fall values, and interrupt generation
		// from the GPIO
		mov r2, #0xff
		str r2, [r1, #GPIO_EXTIFALL]
		str r2, [r1, #GPIO_EXTIRISE]
		str r2, [r1, #GPIO_IEN]

		//Enable interrupt handling in M3 at all. Write 0x802 to ISERO
		ldr r6, =ISER0
		//mov r2, #0x802 wont cut it. 
		//Only 8 bits (or more if the number is symmetric(?))
		//Gets the value from the memory, using "assembler constant pool"
		ldr r2, =#0x802
		str r2, [r6]

        b .  // do nothing


	
	/////////////////////////////////////////////////////////////////////////////
	//
  	// GPIO handler
 	// The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  
		push {lr}

		
		ldr r4, [r3, #GPIO_DIN] 	//Loads the button input
		lsl r4, r4, #8 				//left shifts button to the corresponding led pin
		str r4, [r5, #GPIO_DOUT]	//stores button input on led pins.

		//Loading source of input and clearing it from GPIO_IFC
		ldr r2, [r1, #GPIO_IF]
		str r2, [r1, #GPIO_IFC]

		pop {pc} //return to the content of the link register
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

