CC = gcc
CFLAGS = -ansi -pedantic
LDFLAGS = -lgraph
TARGET = Main

.PHONY: all clean

all: Moving.o Snake.o Main.o $(TARGET)

Moving.o: Moving.c Moving.h
	$(CC) $(CFLAGS) -c Moving.c

Snake.o: Snake.c Moving.h
	$(CC) $(CFLAGS) -c Snake.c

Main.o: Main.c Moving.h Snake.h
	$(CC) $(CFLAGS) -c Main.c

$(TARGET): Snake.o Moving.o
	$(CC) $(CFLAGS) -o Main Main.o Snake.o Moving.o $(LDFLAGS)


run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) Snake.o Moving.o Main.o
