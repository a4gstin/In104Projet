CC = gcc
CFLAGS = -Wall -Werror -Wfatal-errors
LDFLAGS = -lm

TARGET = noperc

SRCS = main.c Functions.c 
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *~ *.o

.PHONY: all clean
