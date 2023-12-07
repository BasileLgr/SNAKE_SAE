CC = gcc
CFLAGS = -ansi -pedantic
LDFLAGS = -lgraph
TARGET = Snake

.PHONY: all clean

all: $(TARGET)

$(TARGET): Snake.c Moving.h Main.c Snake.h
	$(CC) $(CFLAGS) -o $(TARGET) Snake.c Main.c Moving.c $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
