
obj-m += ldm5_core.o ldm5_device.o ldm5_driver.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
