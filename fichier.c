#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"


FILE* ouvre(char const* nom_fichier) 
{
	FILE* fichier = malloc(sizeof *fichier);
  	fichier = fopen(nom_fichier, "r");
  	if (!fichier) 
  	{
	    printf("impossible d'ouvrir fichier %s\n", nom_fichier);
	    exit(1);
  	}
  	return fichier;
}

grille init_file(int size, char* nom_fichier)
{
	int i;
	FILE* fichier;
	fichier = ouvre(nom_fichier);
	grille plateau = initialize(size);

	fichier=ouvre(nom_fichier);
	for (i=0 ; i<size ; i++)
		{
			fgets(plateau[i], size+1, fichier);
			fseek(fichier, 1, SEEK_CUR);
		}
	return plateau;
}

void ferme(FILE* fichier)
{
	fclose(fichier);
	free(fichier);
}

int fin_de_fichier(FILE* fichier) 
{
	return feof(fichier);
}
