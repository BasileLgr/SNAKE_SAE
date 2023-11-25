#include <stdlib.h>
#include <stdio.h>
#define TAILLE_X 40
#define TAILLE_Y 60

int main (void) {
    int grille[TAILLE_X][TAILLE_Y];
    int a =1;
    for (int i = 0; i < TAILLE_X; i++) {
        for (int j = 0; j < TAILLE_Y; j++) {
            grille[i][j] = a;
            a++;
        }
    }
    for (int i = 0; i < TAILLE_X; i++) {
        for (int j = 0; j < TAILLE_Y; j++) {
            printf("%4.d ", grille[i][j]);
        }
        printf("\n");
    }
}