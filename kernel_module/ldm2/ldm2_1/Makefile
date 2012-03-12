KSRCS += ldm2_1.c
KOBJS += $(KSRCS:%.c=%.o)
MODULES_NAME += $(KSRCS:%.c=%.ko)

USRCS += test.c
TARGET += $(USRCS:%.c=%)

obj-m += $(KOBJS)

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	make test

install:
	@insmod $(MODULES_NAME)
	@dmesg -c

run:
	@./$(TARGET)
	@dmesg -c

uninstall:
	@rmmod $(MODULES_NAME)
	@dmesg -c

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	@rm -vf $(TARGET)

.PHONY:$(KSRCS) $(USRCS)
