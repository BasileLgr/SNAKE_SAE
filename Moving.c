#include <stdio.h>
#include <graph.h>
#include "Moving.h"
#include "Snake.h"
#include "Fin.h"

void deplacerSerpent(int tableau[NB_LIGNES][NB_COLONNES], int positionTete[200][2], int *Direction, int *CompteurPommes, int *Score, char tableauScore[10], int position_seconde, int position_minute, int *longeurSerpent) {
    /* Variables pour le déplacement */
    int nouvelleLigne = positionTete[0][0];
    int nouvelleColonne = positionTete[0][1];
    int derniereLigne = positionTete[*longeurSerpent-1][0];
    int derniereColonne = positionTete[*longeurSerpent-1][1];
    int i;
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
        ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
            RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + derniereLigne * TAILLE_CASE,
                DECALAGE_BANDE_NOIR_HAUT + derniereColonne * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
        for(i=0;i<(*longeurSerpent);i++){
            tableau[positionTete[i][1]][positionTete[i][2]]=2;
        }
        for(i = (*longeurSerpent)-1; i >= 1; i--){

        positionTete[i][0] = positionTete[i-1][0];
        positionTete[i][1] = positionTete[i-1][1];
        tableau[positionTete[i][1]][positionTete[i][0]] = 2;
        ChoisirCouleurDessin(CouleurParComposante(240, 255, 70));
        RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + positionTete[i][0] * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + positionTete[i][1] * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
}
        positionTete[0][0] = nouvelleLigne;
        positionTete[0][1] = nouvelleColonne;

        /* Vérifie si la case d'arrivée contient une pomme ou le serpent */
        if (tableau[positionTete[0][1]][positionTete[0][0]] == 1) {
            (*CompteurPommes)--;

            /* Réinitialise la case de la pomme */
            tableau[positionTete[0][0]][positionTete[0][1]] = 0;

            /* Incrémente le score */
            (*Score) += VALEUR_POMME;
            (*longeurSerpent)+=2;

            /* Affichage du score */
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_NOIR));
            RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_TEXTE));
            sprintf(tableauScore, "%07d", *Score);
            EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
        }
        
        tableau[positionTete[0][1]][positionTete[0][0]] = 2;

            /*Affichage de la tete du serpent en fonction de la direction*/
        if(*Direction==GAUCHE) {
            ChargerImage("./Images/TETESERPENTCARREG.png", DECALAGE_BANDE_NOIR_GAUCHE + positionTete[0][0] * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + positionTete[0][1] * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        else if(*Direction==DROITE){
            ChargerImage("./Images/TETESERPENTCARRED.png", DECALAGE_BANDE_NOIR_GAUCHE + positionTete[0][0] * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + positionTete[0][1] * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        else if (*Direction==HAUT){
            ChargerImage("./Images/TETESERPENTCARREH.png", DECALAGE_BANDE_NOIR_GAUCHE + positionTete[0][0] * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + positionTete[0][1] * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        else if (*Direction==BAS){
            ChargerImage("./Images/TETESERPENTCARREB.png", DECALAGE_BANDE_NOIR_GAUCHE + positionTete[0][0] * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + positionTete[0][1] * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        tableau[derniereColonne][derniereLigne]=0;
    } else {
        FermerGraphique();
        fin(*Score, position_minute, position_seconde);
        exit(EXIT_SUCCESS);
    }
}
