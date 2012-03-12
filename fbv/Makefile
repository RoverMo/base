CFLAGS = -Wall


all:bmp

bmp:bmp.h
	$(CC) -Wall	bmp.c	-o	 bmp
	
bmp.h:autoconfig
	sudo ./$^

autoconfig:autoconfig.c

clean:
	@rm -frv bmp auto_config.h autoconfig
