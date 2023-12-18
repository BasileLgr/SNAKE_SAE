#include <stdio.h>
#include <graph.h>
#include "Moving.h"
#include "Snake.h"
#include "Fin.h"

void deplacerSerpent(int tableau[NB_LIGNES][NB_COLONNES], int *ligneDepart, int *colonneDepart, int *Direction, int *CompteurPommes, int *Score, char tableauScore[10], int position_seconde, int position_minute) {
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
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_NOIR));
            RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_TEXTE));
            sprintf(tableauScore, "%07d", *Score);
            EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
        }

        tableau[*colonneDepart][*ligneDepart] = 2;
            /*affichage de la tete du serpent en fonction de la direction*/
        if(*Direction==GAUCHE) {
            ChargerImage("./Images/TETESERPENTCARREG.png", DECALAGE_BANDE_NOIR_GAUCHE + *ligneDepart * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + *colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        else if(*Direction==DROITE){
            ChargerImage("./Images/TETESERPENTCARRED.png", DECALAGE_BANDE_NOIR_GAUCHE + *ligneDepart * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + *colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        else if (*Direction==HAUT){
            ChargerImage("./Images/TETESERPENTCARREH.png", DECALAGE_BANDE_NOIR_GAUCHE + *ligneDepart * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + *colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        else if (*Direction==BAS){
            ChargerImage("./Images/TETESERPENTCARREB.png", DECALAGE_BANDE_NOIR_GAUCHE + *ligneDepart * TAILLE_CASE,
                     DECALAGE_BANDE_NOIR_HAUT + *colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
    
    } else {
        FermerGraphique();
        fin(*Score, position_minute, position_seconde);
    }
}
