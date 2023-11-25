#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#define NB_COLONNES 60
#define NB_LIGNES 40

int main (void) {
    InitialiserGraphique();
    CreerFenetre(10, 10, NB_COLONNES*10, NB_LIGNES*10);
    ChoisirEcran(1);
    return EXIT_SUCCESS;
}