#include <graph.h>
#include "Snake.h"


/*Constante retour du menu*/
#define EXIT_PLAY 1
#define EXIT_QUIT 2

/*Modifiez la fonction menu pour renvoyer le résultat*/
int menu(void) {

    /*Fenêtre de menu*/
    int x, y;
    InitialiserGraphique();
    CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Menu Snake");
    ChargerImageFond("./Images/MENU.png");

    while(1) {

        /*Initialisation clique souris*/
        if (SourisCliquee()) {
            x = _X;
            y = _Y;

            /* Jouer*/
            if ((x > 319) && (x < 533) && (y > 173) && (y < 227)) {
                FermerGraphique();
                return EXIT_PLAY;
            };

            /*Quitter*/
            if ((x > 319) && (x < 533) && (y > 283) && (y < 336)) {
                FermerGraphique();
                return EXIT_QUIT;
            };
        }

        if (ToucheEnAttente()) {
            /*Quitter*/
            if (Touche() == XK_Escape) {
                FermerGraphique();
                return EXIT_QUIT;
            }
            /*Jouer*/
            else if ((Touche() == XK_Return)||(Touche() == XK_space)) {
                FermerGraphique();
                return EXIT_PLAY;
            }
        }
    }
}
