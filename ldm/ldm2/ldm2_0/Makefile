
obj-m += ldm2_0.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	make test

install:
	@sudo insmod ./ldm2_0.ko

run:
	@./test
	@dmesg

uninstall:
	@sudo rmmod ldm2_0
	@sudo dmesg -c

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	@rm -vf test

.PHONY:ldm2_0.c test.c
