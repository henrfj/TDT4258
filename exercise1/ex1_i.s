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

		//Setting internal pull-ups
		mov r4, #0xFF
		str r4, [r3, #GPIO_DOUT]

		
		//Sets what ports are allowed to interrupt
		ldr r1, =GPIO_BASE
		mov r2, #0x22222222
		str r2, [r1, #GPIO_EXTIPSELL]

		//Enables interrupts on rise and fall values
		mov r2, #0xff
		str r2, [r1, #GPIO_EXTIFALL]
		str r2, [r1, #GPIO_EXTIRISE]
		str r2, [r1, #GPIO_IEN]

		//Enable interrupt handling
		ldr r6, =ISER0
		mov r2, #0x0000802
		str r2, [r6]



	
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  
		

		ldr r4, [r3, #GPIO_DIN]
		lsl r4, r4, #8
		str r4, [r5, #GPIO_DOUT]

		ldr r2, [r1, #GPIO_IF]
		str r2, [r1, #GPIO_IFC]

	    b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

