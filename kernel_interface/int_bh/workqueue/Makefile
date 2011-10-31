
obj-m += workqueue.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

install:
	dmesg -c
	insmod workqueue.ko
	dmesg

uninstall:
	rmmod workqueue
	dmesg

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
