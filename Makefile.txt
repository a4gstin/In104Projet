CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = 

TARGET = noperc 

SRCS = main.c p1.c 
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean


