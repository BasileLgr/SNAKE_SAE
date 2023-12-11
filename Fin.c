#include <graph.h>
#include "Snake.h"

#define EXIT_PLAY 1
#define EXIT_QUIT 2

int fin (void){

        int x, y;
        InitialiserGraphique();
        CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
        ChoisirTitreFenetre("Menu Snake");
        ChargerImageFond("./Images/MENUFIN.png");

        while(1) {
            if (SourisCliquee()) {
                x = _X;
                y = _Y;

                /* Jouer*/
                if ((x > 304) && (x < 545) && (y > 230) && (y < 296)) {
                    FermerGraphique();
                    return EXIT_PLAY;
                };

                /*Quitter*/
                if ((x > 315) && (x < 530) && (y > 400) && (y < 457)) {
                    FermerGraphique();
                    return EXIT_QUIT;
                };
            }
        }
    }
