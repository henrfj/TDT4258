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
	

		//Activate clock on GPIO_CONTROLLER
	    ldr r1, =CMU_BASE
		ldr r2, [r1, #CMU_HFPERCLKEN0] 	// loads HFPERCLK ENABLE value

		mov r3, #1
		lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
		orr r2, r2, r3					// prepares value with GPIO clock bit set to 1

		str r2, [r1, #CMU_HFPERCLKEN0]

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
		// Interupt specific setup for BUTTONS
		////////////////////////////////////////////////////////////////////////////


		//Setting BUTTON port to allow interrupts (Port C)
		ldr r1, =GPIO_BASE
		mov r2, #0x22222222
		str r2, [r1, #GPIO_EXTIPSELL]

		//Enables interrupts on rise and fall values, and interrupt generation
		// from the GPIO
		mov r2, #0xff
		str r2, [r1, #GPIO_EXTIFALL] //enable rise
		str r2, [r1, #GPIO_EXTIRISE] //enable fall
		str r2, [r1, #GPIO_IEN] //enable generation

		//Enable interrupt handling in M3 at all. Write 0x802 to ISERO
		ldr r6, =ISER0
		ldr r2, =#0x802
		str r2, [r6]

		//Enable energy mode 2 (sleep mode)
		mov r2, #0x6
		ldr r7, =SCR
		str r2, [r7]

		mov r6, #0x18 //initial value for change_leds
		mvn r4, r6, lsl #8
		str r4, [r5, #GPIO_DOUT]

		wfi  //waits for interrupt

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

		bl change_leds

		//Loading source of input and clearing it from GPIO_IFC
		ldr r2, [r1, #GPIO_IF]
		str r2, [r1, #GPIO_IFC]

		pop {pc} //return to the content of the link register
	
	//------------------- End of handling -----------------------//


	/////////////////////////////////////////////////////////////////////////////
	//
	// Change_leds routine
	// The code below handles the extra logic for the Leds for the fancy solution
	//
	////////////////////////////////////////////////////////////////////////////
	
// r5 is set as the output base while r3 is the input base
// r2 and r4 are used as temporary, hence they are not restored
// register r6 is kept as the value
LEFT   = 0x40
RIGHT  = 0x01
CENTER = 0x14 //actually LEFTR | RIGHTL
UPL    = 0x20
UPR    = 0x02
DOWNL  = 0x80
DOWNR  = 0x08
change_leds:
			// Loading button status onto r4
			ldr r4, [r3, #GPIO_DIN]

			//bic[s] d,a,b <=> d=a & !b; update the status register with s
			//as r4 contains the inverted value (compared to the definition
			//of LEFT) with this bic operation it can be correctly masked and
			//the status register is set (s in bics). Checking for ne (not
			//equal to 0) allows to execute the desired instructions.
			//conditional execution is used here instead of branching
			//arm supports shifting on the second operand in most instructions
			//here we exploit that instead of using a separated instruction

			//left rotate (n<<7 | n>>1)
			ldr r0, =LEFT
			bics r0, r0, r4
			itt ne //if then block
			lsrne r2, r6, #7
			orrne r6, r2, r6, lsl #1 //shifts the second operand!

			//right rotate (n>>7 | n<<1)
			ldr r0, =RIGHT
			bics r0, r0, r4
			itt ne
			lslne r2, r6, #7
			orrne r6, r2, r6, lsr #1

			//mirror (!n) & 0xff
			ldr r0, =CENTER
			bics r0, r0, r4
			it ne
			mvnne r6, r6

			//remove leftmost (n & (n >> 1))
			ldr r0, =DOWNL
			bics r0, r0, r4
			it ne
			andne r6, r6, r6, lsr #1

			//remove rightmost (n & (n << 1))
			ldr r0, =DOWNR
			bics r0, r0, r4
			it ne
			andne r6, r6, r6, lsl #1

			//add leftmost (n | (n << 1))
			ldr r0, =UPL
			bics r0, r0, r4
			it ne
			orrne r6, r6, r6, lsl #1

			//add rightmost (n | (n >> 1))
			ldr r0, =UPR
			bics r0, r0, r4
			it ne
			orrne r6, r6, r6, lsr #1

			//set value 1 if empty
			//cmp r6, #0
			//it eq
			//moveq r6, #1

			and r6, r6, #0xff //ensure register not out of bounds

			//left shifting and negating the input, to match the required input of leds
			mvn r4, r6, lsl #8
			//and r4, r4, #0xff00 //just write those
			str r4, [r5, #GPIO_DOUT]

			mov pc, lr //return

        .thumb_func
dummy_handler:  
        b .  // do nothing

