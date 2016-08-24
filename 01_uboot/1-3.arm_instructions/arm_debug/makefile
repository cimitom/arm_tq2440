all:exp-01.o
	arm-linux-ld -Ttext 0x30000000 -o exp-01.elf $^

%.o:%.S
	arm-linux-gcc -g -c $^

.PHONY:clean
clean:
	rm *.o *.elf
