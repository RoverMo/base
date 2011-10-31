
obj-m += ldm4_dev.o ldm4_drv.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	make test

install:
	insmod ldm4_dev.ko
	insmod ldm4_drv.ko

run:
	./test /dev/ldm4_dev_1
	./test /dev/ldm4_dev_2
	./test /dev/ldm4_dev_3

uninstall:
	rmmod ldm4_dev
	rmmod ldm4_drv

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	@rm -vf test
