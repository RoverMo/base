MAJOR=251

obj-m += ldm2_0.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	make test

install:
	@sudo insmod ./ldm2_0.ko
	@echo "Install module ldm2_0 succese"
	@echo `cat /proc/devices | grep ldm`

run:
	@sudo mknod /dev/ldm2_0 c ${MAJOR} 0
	@echo "Make device node /dev/ldm2_0 succese"
	@./test
	@dmesg

uninstall:
	@sudo rm /dev/ldm* -fv
	@sudo rmmod ldm2_0
	@echo "Remove module ldm2_0 succese"
	@sudo dmesg -c

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	@rm -vf test
.PHONY:ldm2_0.c test.c
