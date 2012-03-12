all: bootloader.bin

bootloader.bin: start.elf
	arm-linux-objcopy -O binary $^ $@

start.elf: start.o
	arm-linux-ld $^ -o $@

start.o: start.S
	arm-linux-gcc -c -nostdinc -nostdlib $^ -o $@

install:
	cp bootloader.bin /work/ -v

clean:
	rm *.bin *.elf *.o
