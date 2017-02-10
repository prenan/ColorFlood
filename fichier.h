#ifndef FICHIER_H
#define FICHIER_H

#include "grille.h"

FILE* ouvre(char const* nom_fichier) ;
grille init_file(int size, char* nom_fichier);
void ferme(FILE* fichier);
int fin_de_fichier(FILE* fichier);

#endif