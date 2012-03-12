
obj-m += tasklet.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

install:
	dmesg -c
	insmod tasklet.ko
	dmesg

uninstall:
	rmmod tasklet
	dmesg

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
