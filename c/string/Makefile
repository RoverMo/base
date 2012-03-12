TARGETS += main
OBJS = string.o main.o

CC = gcc

CFLAGS += -Wall

all : $(TARGETS)

$(TARGETS):$(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -fvr $(OBJS) $(TARGETS) *.o

.PHONY : $(SRCS)
