
1. 	Upload leds_4412.c file to the directory of linux-3.0.86/drivers/char on Ubuntu

2. 	Modify linux-3.0.86/drivers/char/Makefile, add the following line to Makefile
	
	obj-y               += leds_4412.o

3.	Go back to root of linux-3.0.86 and compile the kernel as follows
	
	make zImage

4.	Having finished the compilation, copy the zImage from linux-3.0.86/arch/arm/boot to windows and using minitools to burn the new zImage onto tiny4412 board.

5.	Start the board using the new zImage and check if the /dev/young_leds exists.
