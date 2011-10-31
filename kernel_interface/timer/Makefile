
obj-m += timer.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

install:
	dmesg -c
	insmod timer.ko
	dmesg

uninstall:
	rmmod timer
	dmesg

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
