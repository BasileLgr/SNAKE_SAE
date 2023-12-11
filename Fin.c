#include <graph.h>
#include "Snake.h"
#include "Fin.h"
#include <stdlib.h>

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
                    exit(EXIT_SUCCESS);
                };

                /*Quitter*/
                if ((x > 315) && (x < 530) && (y > 400) && (y < 457)) {
                    FermerGraphique();
                    fonctionsSnake();
                };
            }
        }
    }
