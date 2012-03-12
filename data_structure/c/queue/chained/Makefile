SRCS += $(wildcard *.c)
TARGETS += $(SRCS:%.c=%)

CC = gcc

CFLAGS ?= -Wall

all:$(TARGETS)

clean:
	@rm $(TARGETS) *.o -fvr

.PHONY:$(SRCS)
