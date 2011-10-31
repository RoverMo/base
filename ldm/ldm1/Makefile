SRCS += ldm1.c
OBJS += $(SRCS:%.c=%.o)
MODULES_NAME += $(SRCS:%.c=%.ko)

obj-m += $(OBJS)

all:
	@make -C /lib/modules/`uname -r`/build M=`pwd` modules

install:
	insmod $(MODULES_NAME)
	@dmesg -c

uninstall:
	@rmmod -v $(MODULES_NAME)
	@dmesg -c

clean:
	@make -C /lib/modules/`uname -r`/build M=`pwd` clean

.PHONY:$(SRCS)
