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

                /*Quitter*/
                if ((x > 311) && (x < 523) && (y > 409) && (y < 463)) {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                };

                /*Rejouer*/
                if ((x > 302) && (x < 531) && (y > 237) && (y < 292)) {
                    FermerGraphique();
                    fonctionsSnake();
                };
            }
        }
    }
