SRCS += $(wildcard *.c)
OBJS += $(SRCS:%.c=%)

CFLAGS += -Wall

all:$(OBJS)
	make -C ./string

clean:
	make -C ./string clean
	@rm $(OBJS) *.o -fv

# .PHONY:$(SRCS)
