
obj-m += ldm3_driver.o ldm3_device.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	make test

install:
	insmod ldm3_driver.ko
	insmod ldm3_device.ko

run:
	./test

uninstall:
	rmmod ldm3_device.ko
	rmmod ldm3_driver.ko

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	@rm -fv test
