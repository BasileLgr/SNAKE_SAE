CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ansi -pedantic
LIBS = -lgraph

SRCS = Menu.c Snake.c Moving.c Main.c
OBJS = $(SRCS:.c=.o)

Snake: Menu.o $(filter-out Menu.o, $(OBJS))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: Snake
	./Snake

clean:
	rm -f *.o Snake
