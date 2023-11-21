#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main (void){
    int x,y;
    int curseur;

    InitialiserGraphique();
    CreerFenetre(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    ChoisirTitreFenetre("Snake");
    ChoisirEcran(2 );
    ChargerImageFond ("Images/pinguin.png");
    CopierZone(2,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);

    curseur = ChargerSprite("Images/Curseur.png");

    ChoisirEcran(0);
    while (True) {
        x=_X;
        y=_Y;

        if (SourisCliquee()){
            return EXIT_SUCCESS;
        }
    }
}