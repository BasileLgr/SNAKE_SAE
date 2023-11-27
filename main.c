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
    char chaine[240];
    int position = 0;
    for (int i = 1; i <= 59; ++i) {
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
    EcrireTexte(40,570,"00:00",2);
    unsigned long suivant = Microsecondes() + CYCLE;
    char seconde = '1';
    while (seconde<'9'+1) {

        if (Microsecondes() > suivant) {
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(40,540,NB_COLONNES*TAILLE_CASE,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
            ChoisirCouleurDessin(CouleurParNom("white"));
            EcrireTexte(95,570,&seconde,2);
            EcrireTexte(40,570,"00:0",2);
            ChoisirCouleurDessin(CouleurParNom("black"));
            RemplirRectangle(110,540,NB_COLONNES*TAILLE_CASE,NB_LIGNES*TAILLE_CASE+DECALAGE_MENU_BAS);
            suivant = Microsecondes() + CYCLE;
            seconde++;
        }
    }
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}