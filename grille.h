#include <stdbool.h>
#ifndef GRILLE_H
#define GRILLE_H

struct element
{
	int appartenance;
	char color;
};

typedef struct element element;

typedef element ** grille;

grille initialize(int size);
void display(grille plateau, int size);
grille random(int size);
void free_space(grille plateau, int size);
grille change_color(int i, int j, char c, grille plateau);  /* Change color with index and choosed color--HAO */
bool if_flood(grille plateau, int size);  /* To see whether color flood */

Pile extraire_fils(coordonnees pere, Pile P, char couleur_choisie, grille plateau, int size);
Pile identifier_tache(grille plateau, char couleur_choisie, int size);

#endif
