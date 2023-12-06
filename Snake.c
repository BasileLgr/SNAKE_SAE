#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "Test.h"
#include <time.h>

#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L
#define NOMBRE_POMMES 5
#define COLONNE_DEPART 20
#define LIGNE_DEPART 30
#define COULEUR_FOND 78,184,25
#define DECALAGE_BANDE_NOIR_GAUCHE 40
#define DECALAGE_BANDE_NOIR_HAUT 15
#define X_SCORE 710
#define Y_SCORE 570
#define VALEUR_POMME 5
#define X_TIMER 45
#define Y_TIMER 570
#define X_FENETRE_DE_JEU 200
#define Y_FENETRE_DE_JEU 80

/*Gestion de l'aléatoire*/
void initialiserAleatoire(void) {
    srand((unsigned int)time(NULL));
}

/*Main*/
int main(void) {
    initialiserAleatoire();
    fonctionsSnake();
    return EXIT_SUCCESS;
}


/* Fonction pour générer aléatoirement la ligne des pommes */
int genererLignePommes(int tableau[NB_LIGNES][NB_COLONNES]) {
    int ligne;
    do {
        ligne = rand() % NB_LIGNES;
    } while (tableau[ligne][0] == 1);  /* Vérifier si la ligne est déjà occupée par une pomme */
    return ligne;
}

/* Fonction pour générer aléatoirement la colonne des pommes */
int genererColonnePommes(int tableau[NB_LIGNES][NB_COLONNES]) {
    int colonne;
    do {
        colonne = rand() % NB_COLONNES;
    } while (tableau[0][colonne] == 1);  /* Vérifier si la colonne est déjà occupée par une pomme */
    return colonne;
}


/*Snake*/
void fonctionsSnake(void) {

    int colonneDepart = COLONNE_DEPART;
    int ligneDepart = LIGNE_DEPART;
    unsigned long suivant = Microsecondes() + CYCLE;
    unsigned long suivantTouches = Microsecondes() + CYCLE_TOUCHES;
    /*Pour le timer*/
    int position_seconde = 0;
    int position_minute = 0;
    char temps[10];
    /*Interrupteur pour la boucle, permet de mettre en pause le jeu*/
    int OnOff=1;
    /*Tableau permettant de savoir la position de chaque objet*/
    int tableau[NB_LIGNES][NB_COLONNES];
    /*Permet de savoir en temps réel le nombre de pommes sur le terrain (hors triche)*/
    int CompteurPommes;
    /*Score*/
    int Score = 0;
    char tableauScore[10];
    /*Se souvenir de la direction pour le mouvement*/
    int Direction;

    /*Initialisation du tableau pour s'assurer que les valeurs vides soient à 0*/
    int i, j;
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            tableau[i][j] = 0;
        }
    }

    /*Ouverture de la fenêtre graphique*/
    InitialiserGraphique();

    /*Création de la fenêtre de jeu*/
    CreerFenetre(X_FENETRE_DE_JEU,Y_FENETRE_DE_JEU,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Snake");
    ChoisirCouleurDessin(CouleurParNom("black"));
    RemplirRectangle(0,0,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE,DECALAGE_BANDE_NOIR_HAUT,NB_COLONNES*TAILLE_CASE,NB_LIGNES*TAILLE_CASE);

    /*Mise en place du serpent*/
    ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    tableau[colonneDepart][ligneDepart] = 2;

    /*Mise en places des pommes initiales*/
    for (CompteurPommes = 0; CompteurPommes < NOMBRE_POMMES; ++CompteurPommes) {
        int ligne = genererLignePommes(tableau);
        int colonne = genererColonnePommes(tableau);

        /*Evite de générer deux pommes au même endroit*/
        if (tableau[ligne][colonne] == 1 || tableau[ligne][colonne] == 2) {
            tableau[ligne][colonne] = 0;
            --CompteurPommes;
            continue;
        }

        /*Marque la position de la pomme dans le tableau*/
        tableau[ligne][colonne] = 1;

        /*Affiche les pommes*/
        ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    }
    /*Affichage du timer de départ*/
    ChoisirCouleurDessin(CouleurParNom("white"));
    EcrireTexte(X_TIMER, Y_TIMER, "00:00", 2);

    /*Affichage du score de départ*/
    EcrireTexte(X_SCORE, Y_SCORE, "0000000", 2);

    /*Boucle pour le timer avec interrupteur pour la pause*/
    while (OnOff==1) {

        /*Gestion du temps*/
        if (Microsecondes() > suivant) {

            /*Mise en place de la chaîne de caractères pour le timer*/
            sprintf (temps, "%02d:%02d", position_minute, position_seconde);

            /*Affichage du fond noir pour actualiser le timer*/
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(X_TIMER, Y_TIMER-DECALAGE_BANDE_NOIR_HAUT*2, 75, 40);

            /*Affichage du timer*/
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(X_TIMER, Y_TIMER, temps, 2);

            suivant = Microsecondes() + CYCLE;

            /*Incrémentation des secondes*/
            position_seconde++;

        }

        /*Réinitialisation des secondes et des minutes*/
        if (position_seconde == 60) {
            position_seconde = 0;
            position_minute++;
        }

        /* Apparition d'une nouvelle pomme si nécessaire */
        if (CompteurPommes < NOMBRE_POMMES) {
            int ligne, colonne;
            do {
                ligne = genererLignePommes(tableau);
                colonne = genererColonnePommes(tableau);
            } while (tableau[ligne][colonne] != 0);  /* Vérifier si la case est libre */

            /* Marque la position de la pomme */
            tableau[ligne][colonne] = 1;

            /* Affiche la pomme */
            ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE,
                         DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);

            /* Incrémente le compteur de pommes */
            CompteurPommes++;
        }

        /*Gestion des touches*/
        if (ToucheEnAttente()) {
            int touche = Touche();

            /* Déplacement vers la gauche */
            if (touche == XK_Left) {
                int nouvelleLigne = ligneDepart - 1;

                /* Vérifier si la nouvelle case est valide */
                if (nouvelleLigne >= 0 && nouvelleLigne < NB_COLONNES) {
                    tableau[colonneDepart][ligneDepart] = 0;

                    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
                    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE,
                                     DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, TAILLE_CASE,
                                     TAILLE_CASE);

                    ligneDepart = nouvelleLigne;

                    /* Vérifie si la case d'arrivée contient une pomme */
                    if (tableau[colonneDepart][ligneDepart] == 1) {

                        CompteurPommes--;

                        /* Réinitialise la case de la pomme */
                        tableau[colonneDepart][ligneDepart] = 0;

                        /* Incrémente le score */
                        Score = Score + VALEUR_POMME;

                        /* Affichage du score */
                        ChoisirCouleurDessin(CouleurParNom("black"));
                        RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
                        ChoisirCouleurDessin(CouleurParNom("white"));
                        sprintf(tableauScore, "%07d", Score);
                        EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
                    }

                    tableau[colonneDepart][ligneDepart] = 2;
                    ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE,
                                 DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE,
                                 TAILLE_CASE);
                }

                    /*Fermeture si jamais on touche le bord*/
                else {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
            }



            /* Déplacement vers la droite */
            if (touche == XK_Right) {
                int nouvelleLigne = ligneDepart + 1;

                /* Vérifier si la nouvelle case est valide */
                if (nouvelleLigne >= 0 && nouvelleLigne < NB_COLONNES) {
                    tableau[colonneDepart][ligneDepart] = 0;

                    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
                    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

                    ligneDepart = nouvelleLigne;

                    /* Vérifie si la case d'arrivée contient une pomme */
                    if (tableau[colonneDepart][ligneDepart] == 1) {

                        CompteurPommes--;

                        /* Réinitialise la case de la pomme */
                        tableau[colonneDepart][ligneDepart] = 0;

                        /* Incrémente le score */
                        Score = Score + VALEUR_POMME;

                        /* Affichage du score */
                        ChoisirCouleurDessin(CouleurParNom("black"));
                        RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
                        ChoisirCouleurDessin(CouleurParNom("white"));
                        sprintf(tableauScore, "%07d", Score);
                        EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
                    }

                    tableau[colonneDepart][ligneDepart] = 2;
                    ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
                }
                    /*Fermeture si jamais on touche le bord*/
                else {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
            }

            /* Déplacement vers le haut*/
            if (touche == XK_Up) {
                int nouvelleColonne = colonneDepart - 1;

                /* Vérifier si la nouvelle case est valide */
                if (nouvelleColonne >= 0 && nouvelleColonne < NB_LIGNES) {
                    tableau[colonneDepart][ligneDepart] = 0;

                    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
                    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

                    colonneDepart = nouvelleColonne;

                    /* Vérifie si la case d'arrivée contient une pomme */
                    if (tableau[colonneDepart][ligneDepart] == 1) {
                        CompteurPommes--;

                        /* Réinitialise la case de la pomme */
                        tableau[colonneDepart][ligneDepart] = 0;

                        /* Incrémente le score */
                        Score = Score + VALEUR_POMME;

                        /* Affichage du score */
                        ChoisirCouleurDessin(CouleurParNom("black"));
                        RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
                        ChoisirCouleurDessin(CouleurParNom("white"));
                        sprintf(tableauScore, "%07d", Score);
                        EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
                    }

                    tableau[colonneDepart][ligneDepart] = 2;
                    ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
                }
                    /*Fermeture si jamais on touche le bord*/
                else {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
            }

                /* Gestion de la triche, si on appuie sur "t" on génère une pomme */
            else if (touche == XK_t) {
                int ligne, colonne;

                do {
                    ligne = genererLignePommes(tableau);
                    colonne = genererColonnePommes(tableau);
                } while (tableau[ligne][colonne] == 1 || tableau[ligne][colonne] == 2);

                /* Marque la position de la pomme */
                tableau[ligne][colonne] = 1;

                /* Affiche la pomme */
                ChargerImage("./Images/PommePixel2.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE,
                             DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
            }

            /* Déplacement vers le bas*/
            if (touche == XK_Down) {
                int nouvelleColonne = colonneDepart + 1;

                /* Vérifier si la nouvelle case est valide */
                if (nouvelleColonne >= 0 && nouvelleColonne < NB_LIGNES) {
                    tableau[colonneDepart][ligneDepart] = 0;

                    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
                    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

                    colonneDepart = nouvelleColonne;

                    /* Vérifie si la case d'arrivée contient une pomme */
                    if (tableau[colonneDepart][ligneDepart] == 1) {
                        CompteurPommes--;

                        /* Réinitialise la case de la pomme */
                        tableau[colonneDepart][ligneDepart] = 0;

                        /* Incrémente le score */
                        Score = Score + VALEUR_POMME;

                        /* Affichage du score */
                        ChoisirCouleurDessin(CouleurParNom("black"));
                        RemplirRectangle(X_SCORE, Y_SCORE - DECALAGE_BANDE_NOIR_HAUT * 2, 110, 40);
                        ChoisirCouleurDessin(CouleurParNom("white"));
                        sprintf(tableauScore, "%07d", Score);
                        EcrireTexte(X_SCORE, Y_SCORE, tableauScore, 2);
                    }

                    tableau[colonneDepart][ligneDepart] = 2;
                    ChargerImage("./Images/DenisPixel.png", DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
                }
                    /*Fermeture si jamais on touche le bord*/
                else {
                    FermerGraphique();
                    exit(EXIT_SUCCESS);
                }
            }

                /*Met en pause si on appuie sur espace*/
            else if (touche == XK_space) {
                OnOff = 0;

                /*Reprise si on rappuie sur espace*/
                while (OnOff == 0) {
                    if (Touche() == XK_space) {
                        OnOff = 1;
                    }

                    /*Si jamais on appuie sur échap pendant la pause cela quitte aussi le jeu*/
                    if (Touche() == XK_Escape) {
                        FermerGraphique();
                        exit(EXIT_SUCCESS);
                    }
                }
            }

                /*On quitte le jeu si on appuie sur échap*/
            else if (touche == XK_Escape) {
                FermerGraphique();
                exit(EXIT_SUCCESS);
            }
        }
    }
}
