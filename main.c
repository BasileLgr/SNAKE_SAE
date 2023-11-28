#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#define NB_LIGNES 40
#define NB_COLONNES 60
#define TAILLE_CASE 13
#define DECALAGE_MENU_DG 80
#define DECALAGE_MENU_BAS 60
#define CYCLE 1000000L

int main() {
    char chaine[180];
    int position = 0;
    for (int i = 0; i <= 59; ++i) {
        position += sprintf(chaine + position, "%02d ", i);
    }
    chaine[position - 1] = '\0';
    InitialiserGraphique();
    CreerFenetre(200,80,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirTitreFenetre("Snake");
    ChoisirCouleurDessin(CouleurParNom("black"));
    RemplirRectangle(0,0,NB_COLONNES*TAILLE_CASE+DECALAGE_MENU_DG,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
    ChoisirCouleurDessin(CouleurParComposante(25,200,30));
    RemplirRectangle(40,15,NB_COLONNES*TAILLE_CASE,NB_LIGNES*TAILLE_CASE);
    ChoisirCouleurDessin(CouleurParNom("white"));

    unsigned long suivant = Microsecondes() + CYCLE;
    int i = 0;
    int a = 0;
    while (1){
        if (Microsecondes() > suivant) {
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(45, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(45, 570, &chaine[a], 2);
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(115, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);

            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(75, 570,":", 2);

            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(82, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(84, 570, &chaine[i], 2);
            i = i+3; //décalage dans le tableau
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(115, 540, NB_COLONNES * TAILLE_CASE, NB_LIGNES * TAILLE_CASE + DECALAGE_MENU_BAS);
            suivant = Microsecondes() + CYCLE;
        }
        if (i == 180){
            i = 0;
            a = a+3;
        }
    }
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}