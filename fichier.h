#ifndef FICHIER_H
#define FICHIER_H

#include "grille.h"

int open_file(char const* file_name);
int size_file(char* file_name); /*check files content and return game size if ok*/
grille init_file(int size, char* file_name);
void close_file(int file_in);
int end_of_file(FILE* file);

#endif
