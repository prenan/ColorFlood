#include <stdbool.h>
#ifndef GRILLE_H
#define GRILLE_H

typedef char ** grille;

grille initialize(int size);
void display(grille plateau, int size);
grille random(int size);
void free_space(grille plateau, int size);
grille change_color(int i, int j, char c, grille plateau);  /* Change color with index and choosed color--HAO */
bool if_flood(grille plateau, int size);  /* To see whether color flood */


#endif
