
KERNEL_DIR = /home/young/kun/android/srcs/linux-3.0.86

all:
	make -C $(KERNEL_DIR) M=`pwd` modules

clean:
	make -C $(KERNEL_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= leds_4412.o

