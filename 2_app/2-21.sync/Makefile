C = gcc
CFLAGS = -Wall -O -g -o #编译链接-o
SRCS =$(wildcard *.c)
OBJS =$(patsubst %.c,%,$(SRCS))
.PHONY:all clean
all:$(OBJS)
%:%.c
	$(C) $(CFLAGS) $@ $< -lpthread
clean:
	rm -f $(OBJS)
