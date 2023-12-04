CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -std=c11
LDFLAGS = -lgraph
TARGET = Snake

.PHONY: all clean

all: $(TARGET)

$(TARGET): Snake.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
