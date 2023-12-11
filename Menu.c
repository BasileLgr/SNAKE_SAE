#include <stdio.h>
#include <graph.h>
#include "Snake.h"


/* Ajoutez ces déclarations en haut de Menu.c*/
#define EXIT_PLAY 1
#define EXIT_QUIT 2

/*Modifiez la fonction menu pour renvoyer le résultat*/
int menu(void) {
    int x, y;
    InitialiserGraphique();
    CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Menu Snake");
    ChargerImageFond("./Images/Menu.png");

    while(1) {
        if (SourisCliquee()) {
            x = _X;
            y = _Y;

            /* Jouer*/
            if ((x > 326) && (x < 513) && (y > 230) && (y < 293)) {
                printf("Jouer\n");
                FermerGraphique();
                return EXIT_PLAY;
            };

            /*Quitter*/
            if ((x > 311) && (x < 530) && (y > 385) && (y < 442)) {
                printf("Quitter\n");
                FermerGraphique();
                return EXIT_QUIT;
            };
        }
    }
}
