#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L

int main (void) {

    unsigned long suivant = Microsecondes() + CYCLE;
    int position_seconde = 0;
    int position_minute = 0;
    int compteur_quadrillage;

    InitialiserGraphique();

    //Création de la fenêtre de jeu
    CreerFenetre(200,80,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Snake");
    ChoisirCouleurDessin(CouleurParNom("black"));
    RemplirRectangle(0,0,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirCouleurDessin(CouleurParComposante(78,184,25));
    RemplirRectangle(40,15,NB_COLONNES*TAILLE_CASE,NB_LIGNES*TAILLE_CASE);
    ChoisirCouleurDessin(CouleurParComposante(170,234,12));

    //Mise en place du quadrillage de l'écran de jeu
    for (compteur_quadrillage = 1; compteur_quadrillage < NB_COLONNES; ++compteur_quadrillage) {
        DessinerSegment(40 + TAILLE_CASE * compteur_quadrillage, 15, 40 + TAILLE_CASE * compteur_quadrillage, NB_LIGNES * TAILLE_CASE + 15);
    }
    for (compteur_quadrillage = 1; compteur_quadrillage < NB_LIGNES; ++compteur_quadrillage) {
        DessinerSegment(40, 15 + TAILLE_CASE * compteur_quadrillage, NB_COLONNES * TAILLE_CASE + 40, 15 + TAILLE_CASE * compteur_quadrillage);
    }

    //Boucle pour le timer
    while (1){

        if (Microsecondes() > suivant) {

            //Mise en place de la chaîne de caractères pour le timer
            char temps[10];
            sprintf (temps, "%02d:%02d", position_minute, position_seconde);

            //Affichage du fond noir pour le timer
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(40, 540, 80, 40);

            //Affichage du timer
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(45, 570, temps, 2);

            suivant = Microsecondes() + CYCLE;

            //Incrémentation des secondes
            position_seconde++;

            //Affichage du score (fixe pour le moment)

            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(700, 570,"0000000", 2);
        }

        //Réinitialisation des secondes et des minutes

        if (position_seconde== 60) {
            position_seconde = 0;
            position_minute++;
        }
    }
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}