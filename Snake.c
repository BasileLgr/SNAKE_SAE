#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "Snake.h"
#include "Moving.h"
#include "Main.h"

void fonctionsSnake(void) {
    int colonneDepart = COLONNE_DEPART;
    int ligneDepart = LIGNE_DEPART;
    int lignePositionQueue=LIGNE_DEPART, colonnePositionQueue=COLONNE_DEPART;
    unsigned long vitesseActuelle = VITESSE_INITIALE;
    unsigned long suivant = Microsecondes() + CYCLE;
    unsigned long deplacement = Microsecondes() + vitesseActuelle;
    /* Pour le timer */
    int position_seconde = 0;
    int position_minute = 0;
    char temps[10];
    /* Interrupteur pour la boucle, permet de mettre en pause le jeu */
    int OnOff = 1;
    /* Tableau permettant de savoir la position de chaque objet */
    int tableau[NB_LIGNES][NB_COLONNES];
    /* Permet de savoir en temps réel le nombre de pommes sur le terrain (hors triche) */
    int CompteurPommes;
    int longueurSerpent=1;
    /* Score */
    int Score = 0;
    char tableauScore[10];
    /* Se souvenir de la direction pour le mouvement */
    int Direction = GAUCHE; /* Direction initiale */
    /* Position des pommes */
    int ligne, colonne;

    /* Initialisation du tableau pour s'assurer que les valeurs vides soient à 0 */
    int i, j;
    for (i = 0; i < NB_LIGNES; i++) {
        for (j = 0; j < NB_COLONNES; j++) {
            tableau[i][j] = 0;
        }
    }

    /* Ouverture de la fenêtre graphique */
    InitialiserGraphique();

    /* Création de la fenêtre de jeu */
    CreerFenetre(X_FENETRE_DE_JEU, Y_FENETRE_DE_JEU, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Snake");
    ChoisirCouleurDessin(CouleurParComposante(COULEUR_NOIR));
    RemplirRectangle(0, 0, NB_COLONNES * TAILLE_CASE + DECALAGE_MENU_DG, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
    ChoisirCouleurDessin(CouleurParComposante(COULEUR_FOND));
    RemplirRectangle(DECALAGE_BANDE_NOIR_GAUCHE, DECALAGE_BANDE_NOIR_HAUT, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE);

    /* Mise en place du serpent */
    ChargerImage("./Images/TeteSerpentG.png", DECALAGE_BANDE_NOIR_GAUCHE + ligneDepart * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + colonneDepart * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    tableau[colonneDepart][ligneDepart] = 2;

    /* Mise en places des pommes initiales */
    for (CompteurPommes = 0; CompteurPommes < NOMBRE_POMMES; ++CompteurPommes) {
        genererPositionPomme(tableau, &ligne, &colonne);

        /* Evite de générer deux pommes au même endroit */
        if ((tableau[ligne][colonne] == 1) || (tableau[ligne][colonne] == 2)) {
            tableau[ligne][colonne] = 0;
            --CompteurPommes;
            continue;
        }

        /* Marque la position de la pomme dans le tableau */
        tableau[ligne][colonne] = 1;

        /* Affiche les pommes */
        ChargerImage("./Images/PommePixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE, DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);
    }
    /* Affichage du timer de départ */
    ChoisirCouleurDessin(CouleurParComposante(COULEUR_TEXTE));
    EcrireTexte(X_TIMER, Y_TIMER, "00:00", 2);

    /* Affichage du score de départ */
    EcrireTexte(X_SCORE, Y_SCORE, "0000000", 2);

    /* Boucle principale du jeu */
    while (OnOff == 1) {

        /* Déplacement automatique du serpent */
        if (Microsecondes() > suivant) {
            /* Mise en place de la chaîne de caractères pour le timer */
            sprintf(temps, "%02d:%02d", position_minute, position_seconde);

            /* Affichage du fond noir pour actualiser le timer */
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_NOIR));
            RemplirRectangle(X_TIMER, Y_TIMER - DECALAGE_BANDE_NOIR_HAUT * 2, 75, 40);

            /* Affichage du timer */
            ChoisirCouleurDessin(CouleurParComposante(COULEUR_TEXTE));
            EcrireTexte(X_TIMER, Y_TIMER, temps, 2);

            suivant = Microsecondes() + CYCLE;

            /* Incrémentation des secondes */
            position_seconde++;
            if (position_seconde == 30) {
                vitesseActuelle -= 5000L;
            }
            /* Réinitialisation des secondes et des minutes */
            if (position_seconde == 60) {
                position_seconde = 0;
                position_minute++;
                vitesseActuelle -= 5000L;
            }

            /* Apparition d'une nouvelle pomme si nécessaire */
            if (CompteurPommes < NOMBRE_POMMES) {
                do {
                    genererPositionPomme(tableau, &ligne, &colonne);
                } while (tableau[ligne][colonne] != 0); /* Vérifier si la case est libre */

                /* Marque la position de la pomme */
                tableau[ligne][colonne] = 1;

                /* Affiche la pomme */
                ChargerImage("./Images/PommePixel.png", DECALAGE_BANDE_NOIR_GAUCHE + colonne * TAILLE_CASE,
                             DECALAGE_BANDE_NOIR_HAUT + ligne * TAILLE_CASE, 0, 0, TAILLE_CASE, TAILLE_CASE);

                /* Incrémente le compteur de pommes */
                CompteurPommes++;
            }

        }
        if(Microsecondes()>deplacement){
            /* Déplacer le serpent selon la direction actuelle */

            deplacerSerpent(tableau, &ligneDepart, &colonneDepart, &Direction, &CompteurPommes, &Score, tableauScore, &longueurSerpent, &lignePositionQueue, &colonnePositionQueue);
            deplacement = Microsecondes() + vitesseActuelle;
        }
        if (ToucheEnAttente()) {
            int touche = Touche();
            /*empechement du 180°*/
            if (touche == XK_Left && Direction != DROITE) {
                Direction = GAUCHE;
            }
            if (touche == XK_Right && Direction != GAUCHE) {
                Direction = DROITE;
            }
            if (touche == XK_Up && Direction != BAS) {
                Direction = HAUT;
            }
            if (touche == XK_Down && Direction != HAUT) {
                Direction = BAS;
            }
            /*Met en pause si on appuie sur espace*/
            if (touche == XK_space) {
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
