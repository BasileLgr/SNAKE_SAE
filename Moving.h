#ifndef MOVING_H
#define MOVING_H

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "Snake.h"
#include <time.h>

#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L
#define VITESSE_INITIALE 150000L
#define NOMBRE_POMMES 5
#define COLONNE_DEPART 20
#define LIGNE_DEPART 30
#define COULEUR_FOND 78, 184, 25
#define DECALAGE_BANDE_NOIR_GAUCHE 40
#define DECALAGE_BANDE_NOIR_HAUT 15
#define X_SCORE 710
#define Y_SCORE 570
#define VALEUR_POMME 5
#define X_TIMER 45
#define Y_TIMER 570
#define X_FENETRE_DE_JEU 200
#define Y_FENETRE_DE_JEU 80

enum Direction {
    GAUCHE,
    DROITE,
    HAUT,
    BAS
};

void deplacerSerpent(int tableau[NB_LIGNES][NB_COLONNES], int *ligneDepart, int *colonneDepart, int *Direction, int *CompteurPommes, int *Score, char tableauScore[10]);

#endif
