CC = gcc
CFLAGS = -Wall -Werror -Wfatal-errors
LDFLAGS = -lm

TARGET = noperc

SRCS = main3.c p1.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *~ *.o

.PHONY: all clean
