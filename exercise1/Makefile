# Example Makefile
#
# Exercise 1, TDT4258

SRC?=ex1_i_fancy.s #default build
LD=arm-none-eabi-gcc
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy

LDFLAGS=-nostdlib
ASFLAGS=-mcpu=cortex-m3 -mthumb -g

LINKERSCRIPT=efm32gg.ld

ex1.bin : ex1.elf
	${OBJCOPY} -j .text -O binary $< $@

ex1.elf : ex1.o 
	${LD} -T ${LINKERSCRIPT} $^ -o $@ ${LDFLAGS} 

ex1.o : ${SRC}
	${AS} ${ASFLAGS} $< -o $@

.PHONY : upload
upload :
	-eACommander.sh -r --address 0x00000000 -f "ex1.bin" -r

.PHONY : clean
clean :
	-rm -rf *.o *.elf *.bin *.hex

.PHONY : poll, irq, f_poll, f_irq
poll : clean
	@SRC=ex1_p.s $(MAKE)
irq : clean
	@SRC=ex1_i.s $(MAKE)
f_poll : clean
	@SRC=ex1_p_fancy.s $(MAKE)
f_irq : clean
	@SRC=ex1_i_fancy.s $(MAKE)
