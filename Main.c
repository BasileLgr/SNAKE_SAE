#include <stdlib.h>
#include <graph.h>
#include "Snake.h"
#include <time.h>

/* Gestion de l'aléatoire */
void initialiserAleatoire(void) {
    srand((unsigned int)time(NULL));
}

/* Main */
int main(void) {
    initialiserAleatoire();
    fonctionsSnake();
    return EXIT_SUCCESS;
}

/* Fonction pour générer aléatoirement la position des pommes */
void genererPositionPomme(int tableau[NB_LIGNES][NB_COLONNES], int *ligne, int *colonne) {
    do {
        *ligne = rand() % NB_LIGNES;
        *colonne = rand() % NB_COLONNES;
    } while ((tableau[*ligne][*colonne] == 1) || (tableau[*ligne][*colonne] == 2)); /* Vérifier si la position est déjà occupée par une pomme ou le serpent */
}
