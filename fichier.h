#ifndef FICHIER_H
#define FICHIER_H

#include "grille.h"

FILE* open_file(char const* file_name);
grille init_file(int size, char* file_name);
void close_file(FILE* file);
int end_of_file(FILE* file);

#endif