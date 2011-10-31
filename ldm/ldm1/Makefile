SRCS += ldm1.c
OBJS += $(SRCS:%.c=%.o)
MODULES_NAME += $(SRCS:%.c=%.ko)

obj-m += $(OBJS)

all:
	echo $(OBJS)
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

install:
	dmesg -c
	insmod $(MODULES_NAME)
	dmesg

uninstall:
	@rmmod -v $(MODULES_NAME)
	dmesg

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

.PHONY:$(SRCS)
