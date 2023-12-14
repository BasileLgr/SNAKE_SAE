#include <graph.h>
#include "Snake.h"
#include <stdlib.h>
#include <stdio.h>

int fin (int score){

        /*Fenêtre de fin si on meurt*/
        int x, y;
        char tableauScore[10];
        InitialiserGraphique();
        CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
        ChoisirTitreFenetre("Menu Snake");
        ChargerImageFond("./Images/MENUFIN.png");
    ChoisirCouleurDessin(CouleurParComposante(COULEUR_TEXTE));
    sprintf(tableauScore, "%07d", score);
    EcrireTexte(480, 230, tableauScore, 2);


        while(1) {

            /*Initialisation clique souris*/
            if (SourisCliquee()) {
                x = _X;
                y = _Y;

                /*Quitter*/
                if ((x > 116) && (x < 331) && (y > 279) && (y < 332)) {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                };

                /*Rejouer*/
                if ((x > 117) && (x < 332) && (y > 178) && (y < 232)) {
                    FermerGraphique();
                    fonctionsSnake();
                };
            }
        }
    }
