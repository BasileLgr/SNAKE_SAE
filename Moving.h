#ifndef MOVING_H
#define MOVING_H

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "Snake.h"
#include <time.h>

#define VALEUR_POMME 5

enum Direction {
    GAUCHE,
    DROITE,
    HAUT,
    BAS
};


void deplacerSerpent(int tableau[NB_LIGNES][NB_COLONNES], int positionTete[200][2], int *Direction, int *CompteurPommes, int *Score, char tableauScore[10], int position_seconde, int position_minute, int *longueurSerpent);

#endif
