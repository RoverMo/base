SRCS += $(wildcard *.c)
OBJS += $(SRCS:%.c=%)

CFLAGS ?= -Wall

all:$(OBJS)

clean:
	@rm $(OBJS) *.o -fvr

.PHONY:$(SRCS)
