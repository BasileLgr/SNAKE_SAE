#include <graph.h>
#include "Snake.h"
#include <stdlib.h>
#include <stdio.h>


int fin (int score, int position_minute, int position_seconde){

        /*Fenêtre de fin si on meurt*/
        int x, y;
        char tempsFinal[10];
        char tableauScore[10];
        InitialiserGraphique();
        CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
        ChoisirTitreFenetre("Menu Snake");
        ChargerImageFond("./Images/MENUFIN.png");

        /*Affichage du score de fin*/
        ChoisirCouleurDessin(CouleurParComposante(COULEUR_TEXTE));
        sprintf(tableauScore, "%07d", score);
        EcrireTexte(480, 235, tableauScore, 2);

        /*Affichage du timer de fin*/
        sprintf(tempsFinal, "%02d:%02d", position_minute, position_seconde);
        EcrireTexte(480, 335, tempsFinal, 2);



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
            if (ToucheEnAttente()) {
                if (Touche() == XK_Escape) {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
                /*Rejouer*/
                else if (Touche() == XK_r) {
                    FermerGraphique();
                    fonctionsSnake();
                }
            }
        }
    }
