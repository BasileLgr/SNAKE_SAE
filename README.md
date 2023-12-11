# Jeu du Serpent en C

## Introduction
Ce projet consiste en l'implémentation d'une version du jeu classique du Serpent en langage C. Le joueur contrôle un serpent en mouvement constant qui doit manger des pastilles sans percuter les limites du terrain ou sa propre queue.

## Démarrage
Pour compiler et exécuter le jeu, utilisez le Makefile fourni :
```bash
make
make run
'''

## Contrôles
- Utilisez les touches directionnelles (← ↑ → ↓) pour changer la direction du serpent.
- Appuyez sur `Esc` pour quitter le jeu.
- Appuyez sur `Espace` pour mettre le jeu en pause et le reprendre.

## Règles du jeu
- Le terrain de jeu est une grille de 40 lignes par 60 colonnes.
- 5 pastilles de la taille d'une case sont placées aléatoirement.
- Le serpent, constitué de 10 segments, est initialement placé au milieu.
- Le serpent avance en ajoutant un segment en tête et en enlevant un segment en queue.
- Si le serpent percute les limites du terrain ou sa propre queue, la partie se termine.
- Manger une pastille augmente le score et la longueur du serpent.
- Si la case où doit être ajouté un segment est hors du terrain ou déjà occupée, la partie se termine.
- Si un segment est ajouté sur une pastille, elle est "mangée". Une nouvelle pastille est placée aléatoirement, et le serpent s'allonge de 2 segments.

## Variante
- Le déplacement du serpent s'accélère en fonction du score ou du temps écoulé.

## Fichiers et Structure
- `Main.c` : Fonction principale et boucle de jeu.
- `Snake.c` : Implémentation de la logique du serpent.
- `Moving.c` : Déplacement du serpent.
- `Makefile` : Commandes de compilation et d'exécution.

## Dépendances
Ce projet utilise la bibliothèque graphique de l'IUT. Assurez-vous qu'elle est correctement installée et liée lors de la compilation.

## Collaboration
Le code source est disponible sur le serveur Gitea du département dans le dépôt privé nommé `SAE11_2023`.
