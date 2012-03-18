KSRCS += ldm2.c
KOBJS += $(KSRCS:%.c=%.o)
MODULES_NAME += $(KSRCS:%.c=%)
MODULES_FILE = $(MODULES_NAME).ko

USRCS += test.c
TARGET += $(USRCS:%.c=%)
MAJOR = `awk '/$(MODULES_NAME)/{print $$1}' /proc/devices`

obj-m += $(KOBJS)

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	make test

install:
	@insmod $(MODULES_FILE)
	@mknod /dev/$(MODULES_NAME) c $(MAJOR) 0
	@dmesg -c

run:
	@./$(TARGET)
	@dmesg -c

uninstall:
	@rmmod $(MODULES_FILE)
	@dmesg -c

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	@rm -vf $(TARGET)

.PHONY:$(KSRCS) $(USRCS) test
