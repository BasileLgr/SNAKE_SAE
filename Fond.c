#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "Fond.h"
#include <time.h>

#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L
#define NOMBRE_POMMES 5

//Gestion de l'aléatoire
void initialiserAleatoire() {
    srand((unsigned int)time(NULL));
}

int main (void){
    initialiserAleatoire();
    fonctionsFond();
    return EXIT_SUCCESS;
}

//Fonction pour generer la aleatoirement la ligne des pommes
int genererLignePommes(){
    return rand() % 40; // Génère un nombre entre 0 et 40
}

//Fonction pour generer la aleatoirement la colonne des pommes
int genererColonnePommes(){
    return rand() % 60; // Génère un nombre entre 0 et 60
}

void fonctionsFond() {

    unsigned long suivant = Microsecondes() + CYCLE;
    int position_seconde = 0;
    int position_minute = 0;
    int compteur_quadrillage;
    int OnOff=1;
    int tableau[NB_LIGNES][NB_COLONNES];
    int CompteurPommes;

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

    //Mise en places des pommes initiales
    for (CompteurPommes = 0; CompteurPommes < NOMBRE_POMMES; ++CompteurPommes) {
        int ligne = genererLignePommes();
        int colonne = genererColonnePommes();
        //Evite de générer deux pommes au même endroit
        if (tableau[ligne][colonne] == 1) {
            --CompteurPommes;
            continue;
        }
        tableau[ligne][colonne] = 1;
        ChargerImage("./images/PommePixel.png", 40 + colonne * TAILLE_CASE, 15 + ligne * TAILLE_CASE, 0, 0, 13, 13);
    }

    //Boucle pour le timer
    while (OnOff==1){

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

        //Gestion de la triche, si on appuie sur "t" on génère une pomme
        if (ToucheEnAttente() && Touche() == XK_t) {
            int ligne = genererLignePommes();
            int colonne = genererColonnePommes();
            //Evite de générer deux pommes au même endroit
            if (tableau[ligne][colonne] == 1) {
                --CompteurPommes;
                continue;
            }
            tableau[ligne][colonne] = 1;
            ChargerImage("./images/PommePixel.png", 40 + colonne * TAILLE_CASE, 15 + ligne * TAILLE_CASE, 0, 0, 13, 13);
        }

        if (ToucheEnAttente() && Touche() == XK_t) {
            CompteurPommes--;
        }

        //Apparition d'une nouvelle pomme
        if (CompteurPommes < 5){
            tableau[genererLignePommes()][genererColonnePommes()] = 1;
            CompteurPommes++;
        }

        //Fermeture de la fenêtre si on appuie sur échap
        if (ToucheEnAttente() && Touche() == XK_Escape) {
            FermerGraphique();
            exit(EXIT_SUCCESS);
        }

        //Pause du jeu si on appuie sur espace
        if (ToucheEnAttente() && Touche() == XK_space) {
            OnOff=0;
            while (OnOff==0){
                if (ToucheEnAttente() && Touche() == XK_space) {
                    OnOff=1;
                }

                //Si jamais on appuie sur échap pendant la pause cela quitte aussi le jeu
                if (ToucheEnAttente() && Touche() == XK_Escape) {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
            }
        }

    }
}