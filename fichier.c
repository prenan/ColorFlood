#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"


FILE* open_file(char const* file_name)
{
	FILE* file = malloc(sizeof * file);
  	file = fopen(file_name, "r");
  	if (!file) 
  	{
	    printf("impossible d'ouvrir file %s\n", file_name);
	    exit(1);
  	}
  	return file;
}
/*
int size_file(char* file_name)
{
	compte nombre de lignes (de \n dans fichier txt)
	compte nombre de caractères au total
	compte nb de caractère sur 1ère ligne (sans le \n)
	OK si (nb_caractère_1ère_ligne + 1) * nb_lignes = nb_de_caract

	renvoie -1 si pb
}
*/
grille init_file(int size, char* file_name)
{
	int i;
	FILE* file;
	file = open_file(file_name);

	grille plateau = initialize(size);
	for (i=0 ; i<size ; i++)
	{
		fgets(plateau[i], size+1, file);
		fseek(file, 1, SEEK_CUR);
	}

	return plateau;
}

void close_file(FILE* file)
{
	fclose(file);
	free(file);
}

int end_of_file(FILE* file)
{
	return feof(file);
}
