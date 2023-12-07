CC = gcc
CFLAGS = -ansi -pedantic
LDFLAGS = -lgraph
TARGET = Snake

.PHONY: all clean

all: Moving.o Snake.o $(TARGET)

Moving.o: Moving.c Moving.h
	$(CC) $(CFLAGS) -c Moving.c

Snake.o: Snake.c Moving.h
	$(CC) $(CFLAGS) -c Snake.c

$(TARGET): Snake.o Moving.o
	$(CC) $(CFLAGS) -o Snake Snake.o Moving.o $(LDFLAGS)


run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) Snake.o Moving.o
