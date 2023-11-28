all: fond serpent

fond: fond.c
	gcc -ansi -pedantic -lgraph -o fond fond.c
	./fond &

serpent: serpent.c
	gcc -ansi -pedantic -lgraph -o serpent serpent.c
	./serpent &
