#include <graph.h>
#include "Snake.h"
#include "Fin.h"
#include <stdlib.h>

int fin (void){

        /*Fenêtre de fin si on meurt*/
        int x, y;
        InitialiserGraphique();
        CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
        ChoisirTitreFenetre("Menu Snake");
        ChargerImageFond("./Images/MENUFIN.png");

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
