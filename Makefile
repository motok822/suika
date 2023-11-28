CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

suika: $(OBJS)
		$(CC) -o suika $(OBJS) $(LDFLAGS)

$(OBJS): suika.h

test: ./suika