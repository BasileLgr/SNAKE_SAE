#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "Snake.h"
#include <time.h>

#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L
#define NOMBRE_POMMES 5
#define CYCLE_TOUCHES 100000L
#define COLONNE_DEPART 30
#define LIGNE_DEPART 20
#define COULEUR_FOND 78,184,25
#define DECALAGE_BANDE_NOIR_GAUCHE 40
#define DECALAGE_BANDE_NOIR_HAUT 15

/*Gestion de l'aléatoire*/
void initialiserAleatoire() {
    srand((unsigned int)time(NULL));
}

/*Main*/
int main (void){
    initialiserAleatoire();
    fonctionsSnake();
    return EXIT_SUCCESS;
}

/*Fonction pour generer la aleatoirement la ligne des pommes*/
int genererLignePommes(){
    return rand() % NB_LIGNES; /*Génère un nombre entre 0 et le nombre de lignes*/
}

/*Fonction pour generer la aleatoirement la colonne des pommes*/
int genererColonnePommes(){
    return rand() % NB_COLONNES; /*Génère un nombre entre 0 et le nombre de colonnes*/
}

/*Snake*/
void fonctionsSnake() {

    int colonneDepart = COLONNE_DEPART;
    int ligneDepart = LIGNE_DEPART;
    unsigned long suivant = Microsecondes() + CYCLE;
    /*Pour le timer*/
    int position_seconde = 0;
    int position_minute = 0;
    /*Interrupteur pour la boucle, permet de mettre en pause le jeu*/
    int OnOff=1;
    /*Tableau permettant de savoir la position de chaque objet*/
    int tableau[NB_LIGNES][NB_COLONNES];
    /*Permet de savoir en temps réel le nombre de pommes sur le terrain (hors triche)*/
    int CompteurPommes;

    /*Ouverture de la fenêtre graphique*/
    InitialiserGraphique();

    /*Création de la fenêtre de jeu*/
    CreerFenetre(200,80,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Snake");
    ChoisirCouleurDessin(CouleurParNom("black"));
    RemplirRectangle(0,0,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE,DECALAGE_BANDE_NOIR_HAUT,NB_COLONNES*TAILLE_CASE,NB_LIGNES*TAILLE_CASE);

    /*Mise en place du serpent*/
    ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    tableau[colonneDepart][ligneDepart] = 2;

    /*Mise en places des pommes initiales*/
    for (CompteurPommes = 0; CompteurPommes < NOMBRE_POMMES; ++CompteurPommes) {
        int ligne = genererLignePommes();
        int colonne = genererColonnePommes();

        /*Evite de générer deux pommes au même endroit*/
        if (tableau[ligne][colonne] == 1) {
            --CompteurPommes;
            continue;
        }

        /*Marque la position de la pomme dans le tableau*/
        tableau[ligne][colonne] = 1;

        /*Affiche les pommes*/
        ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    }

    /*Boucle pour le timer avec interrupteur pour la pause*/
    while (OnOff==1){

        /*Gestion du temps*/
        if (Microsecondes() > suivant) {

            /*Mise en place de la chaîne de caractères pour le timer*/
            char temps[10];
            sprintf (temps, "%02d:%02d", position_minute, position_seconde);

            /*Affichage du fond noir pour actualiser le timer*/
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE, 540, 80, 40);

            /*Affichage du timer*/
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(45, 570, temps, 2);

            suivant = Microsecondes() + CYCLE;

            /*Incrémentation des secondes*/
            position_seconde++;

            /*Affichage du score (fixe pour le moment)*/
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(700, 570,"0000000", 2);
        }

        /*Réinitialisation des secondes et des minutes*/
        if (position_seconde== 60) {
            position_seconde = 0;
            position_minute++;
        }

        /*Gestion de la triche, si on appuie sur "t" on génère une pomme*/
        if (ToucheEnAttente() && Touche() == XK_t) {
            int ligne = genererLignePommes();
            int colonne = genererColonnePommes();

            /*Evite de générer deux pommes au même endroit*/
            if (tableau[ligne][colonne] != 1) {
                /*Marque la position de la pomme
                tableau[ligne][colonne] = 1;

                /*Affiche la pomme*/
                ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
                /*Regénère d'autre coordonées pour éviter les doublons*/
            else {
                int ligne = genererLignePommes();
                int colonne = genererColonnePommes();
                tableau[ligne][colonne] = 1;

                /*Affiche la pomme*/
                ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }
        }

        /*Apparition d'une nouvelle pomme si nécessaire*/
        if (CompteurPommes < NOMBRE_POMMES) {
            int ligne = genererLignePommes();
            int colonne = genererColonnePommes();

            /*Evite de générer deux pommes au même endroit*/
            if (tableau[ligne][colonne] == 1) {
                continue;
            }

            /*Marque la position de la pomme*/
            tableau[ligne][colonne] = 1;

            /*Affiche la pomme*/
            ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);

            /*Incrémente le compteur de pommes*/
            CompteurPommes++;
        }

        /*Déplacement vers la gauche*/
        if (ToucheEnAttente() && (Touche() == XK_Left)) {
                tableau[colonneDepart][ligneDepart] = 0;

                ChoisirCouleurDessin(CouleurParComposante(78, 184, 25));
                RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
                colonneDepart--;
            /*Vérifie si il y a une pomme sur la case d'arrivée*/
                if (tableau[colonneDepart][ligneDepart] == 1) {
                    CompteurPommes--;
                    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
                }
                tableau[colonneDepart][ligneDepart] = 2;
                ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
        }

        /*Déplacement vers la droite*/
        if (ToucheEnAttente() && (Touche() == XK_Right)) {
            tableau[colonneDepart][ligneDepart] = 0;
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
            RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            colonneDepart++;
            /*Vérifie si il y a une pomme sur la case d'arrivée*/
            if (tableau[colonneDepart][ligneDepart] == 1) {
                CompteurPommes--;
                RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            }
            tableau[colonneDepart][ligneDepart] = 2;
            ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
        }

        /*Déplacement vers le haut*/
        if (ToucheEnAttente() && (Touche() == XK_Up)) {
            tableau[colonneDepart][ligneDepart] = 0;
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
            RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            ligneDepart--;
            /*Vérifie si il y a une pomme sur la case d'arrivée*/
            if (tableau[colonneDepart][ligneDepart] == 1) {
                CompteurPommes--;
                RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            }
            tableau[colonneDepart][ligneDepart] = 2;
            ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
        }

        /*Déplacement vers le bas*/
        if (ToucheEnAttente() && (Touche() == XK_Down)) {
            tableau[colonneDepart][ligneDepart] = 0;
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
            RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            ligneDepart++;
            /*Vérifie si il y a une pomme sur la case d'arrivée*/
            if (tableau[colonneDepart][ligneDepart] == 1) {
                CompteurPommes--;
                RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
            }
            tableau[colonneDepart][ligneDepart] = 2;
            ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
        }

        /*Fermeture de la fenêtre si on appuie sur échap*/
        if (ToucheEnAttente() && (Touche() == XK_Escape)) {
            FermerGraphique();
            exit(EXIT_SUCCESS);
        }

        /*Pause du jeu si on appuie sur espace*/
        if (ToucheEnAttente() && (Touche() == XK_space)) {
            OnOff=0;

            /*Reprise si on rappuie sur espace*/
            while (OnOff==0){
                if (ToucheEnAttente() && (Touche() == XK_space)) {
                    OnOff=1;
                }

                /*Si jamais on appuie sur échap pendant la pause cela quitte aussi le jeu*/
                if (ToucheEnAttente() && (Touche() == XK_Escape)) {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}