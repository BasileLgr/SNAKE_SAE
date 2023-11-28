all: Main

Main: serpent.o main.o
	gcc -o Main serpent.o main.o -lgraph -ansi -pedantic

serpent.o: serpent.c
	gcc -c -o serpent.o serpent.c

main.o: main.c
	gcc -c -o main.o main.c

clean:
	rm -f serpent.o main.o Main
