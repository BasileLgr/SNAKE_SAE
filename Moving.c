#include <stdio.h>
#include <graph.h>
#include "Moving.h"
#include "Snake.h"
#include "Fin.h"

void deplacerSerpent(int tableau[NB_LIGNES][NB_COLONNES], int *ligneDepart, int *colonneDepart, int *Direction, int *CompteurPommes, int *Score, char tableauScore[10]) {
    int nouvelleLigne = *ligneDepart;
    int nouvelleColonne = *colonneDepart;

    /* Déplacer le serpent selon la direction actuelle */
    switch (*Direction) {
        case GAUCHE:
            nouvelleLigne--;
            break;
        case DROITE:
            nouvelleLigne++;
            break;
        case HAUT:
            nouvelleColonne--;
            break;
        case BAS:
            nouvelleColonne++;
            break;
    }

    /* Vérifier si la nouvelle case est valide */
    if ((nouvelleLigne >= 0 && nouvelleLigne < NB_COLONNES && nouvelleColonne >= 0 && nouvelleColonne < NB_LIGNES) && (tableau[nouvelleColonne][nouvelleLigne] != 2)) {
        tableau[*colonneDepart][*ligneDepart] = 0;

        ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
        RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + *ligneDepart * TAILLE_CASE,
                         DECALAGE_BANDE_NOIR_HAUT + *colonneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

        *ligneDepart = nouvelleLigne;
        *colonneDepart = nouvelleColonne;

        /* Vérifie si la case d'arrivée contient une pomme ou le serpent */
        if (tableau[*colonneDepart][*ligneDepart] == 1) {
            (*CompteurPommes)--;

            /* Réinitialise la case de la pomme */
            tableau[*colonneDepart][*ligneDepart] = 0;

            /* Incrémente le score */
            (*Score) += VALEUR_POMME;

            /* Affichage du score */
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
            ChoisirCouleurDessin(CouleurParNom("white"));
            sprintf(tableauScore, "%07d", *Score);
            EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
        }

        tableau[*colonneDepart][*ligneDepart] = 2;
        ChargerImage("./Images/TeteSerpentG.png", DECALAGE_BANDE_NOIR_GAUCHE + *ligneDepart * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + *colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    } else {
        FermerGraphique();
        fin();
    }
}
