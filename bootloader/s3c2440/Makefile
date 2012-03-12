
TARGET=mwloader

OBJS = start.o init.o 

CROSS_COMPILE = arm-maxwit-linux-gnueabi-

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS := -ffreestanding -nostdinc -nostdlib -fno-builtin -mno-thumb-interwork -march=armv4t -mabi=aapcs-linux 
CFLAGS += -I.
LDFLAGS =-m armelf_linux_eabi

ASFLAGS := $(CFLAGS) -D__ASEMBLY__

all:$(TARGET).bin

$(TARGET).elf:$(OBJS)
	$(LD) $(LDFLAGS) -T bootloader.lds $^ -o $@

$(TARGET).bin:$(TARGET).elf
	$(OBJCOPY) -O binary -S $< $@

.s.o:
	$(CC) $(ASFLAGS) -c  $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c  $^ -o $@

clean:
	rm -rf *.o $(TARGET).*
