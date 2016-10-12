obj-m := memdev.o
KDIR := /arm/linux-2.6.30.4
all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
clean:
	rm -f *.o *.order *.ko *.mod.c *.mod.o *.symvers