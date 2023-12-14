CC = gcc
CFLAGS = -ansi -pedantic
LDFLAGS = -lgraph

# Liste des fichiers sources
SRCS = Menu.c Snake.c Moving.c Main.c Fin.c

# Cible principale
Snake: $(SRCS)
	$(CC) -o Snake $(SRCS) $(CFLAGS) $(LDFLAGS)

# Cible pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f Snake

# Cible pour exécuter le programme
run: Snake
	./Snake

.PHONY: Snake clean run
