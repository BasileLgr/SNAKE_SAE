#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L

int main(void) {

    int compteur_quadrillage;
    int compteur_valeur_seconde;
    char chaine[180]; //Chaîne de caractère contenant les valeurs de 00 à 59 pour le temps
    int position = 0;
    for (compteur_valeur_seconde = 0; compteur_valeur_seconde <= 59; ++compteur_valeur_seconde) {
        position += sprintf(chaine + position, "%02d ", compteur_valeur_seconde);
    }
    chaine[position - 1] = '\0';

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



    unsigned long suivant = Microsecondes() + CYCLE;
    int position_seconde = 0;
    int position_minute = 0;

    while (1){
        if (Microsecondes() > suivant) {

            //Affichage des secondes
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(45, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(45, 570, &chaine[position_minute], 2);
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(115, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);

            //Séparation des secondes et des minutes
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(75, 570,":", 2);

            //Affichage des minutes
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(82, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(84, 570, &chaine[position_seconde], 2);
            position_seconde = position_seconde+3; //décalage dans le tableau

            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(115, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
            suivant = Microsecondes() + CYCLE;

            //Affichage du score (fixe pour le moment)
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(700, 570,"0000000", 2);
        }

        //Réinitialisation des secondes et des minutes
        if (position_seconde == 180){
            position_seconde = 0;
            position_minute = position_minute+3;
        }
    }
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}