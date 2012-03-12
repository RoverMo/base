SRCS += $(wildcard *.c)
OBJS += $(SRCS:%.c=%)

CFLAGS ?= -Wall
LDFLAGS ?= -lpthread

all:$(OBJS)

clean:
	@rm $(OBJS) *.o -fvr

.PHONY:$(SRCS)
