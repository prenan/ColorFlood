#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"


FILE* open_file(char const* file_name)
{
	FILE* file = malloc(sizeof * file);
	file = fopen(file_name, "r");
	if (!file) 
	{
		printf("impossible d'ouvrir le fichier %s\n", file_name);
		exit(1);
	}
	return file;
}

int size_file(char* file_name)
{
	int size, nb_char = 0, nb_char_line1 = 0, nb_lines = 1;
	char text[601];
	FILE* file;
	file = open_file(file_name);
/*	fread(text, 601, 1, file);*/	/*contenu du fichier dans text*/


	while (fread(text, 601, 1, file) != 0)	/*compte le nb de caractères au total (sans le \0)
									et le nb de lignes*/
	{
		if (text[nb_char] == '\n')
		{
			nb_lines = nb_lines+1;
		}
		nb_char = nb_char+1;
	}

	while (text[nb_char] != '\n')	/*compte le nb de caractères sur la 1ère ligne*/
	{
		nb_char_line1++;
		nb_char++;
	}

	if ((nb_char_line1 + 1)*nb_lines == nb_char+1)	/*si on a bien un carré, le fichier "est bien rédigé"*/
	{
		size = nb_char_line1;
	}
	else
	{
		size = -1;
	}

	if (size == -1)
	{
		printf("contenu du fichier %s erroné\n", file_name);
		exit(1);
	}

	return size;
}

grille init_file(int size, char* file_name)
{
	int i,j;
	char* buffer=calloc(size,sizeof(char));
	FILE* file;
	file = open_file(file_name);

	grille plateau = initialize(size);
	for (i=0 ; i<size ; i++)
	{
		fgets(buffer,size+1,file);
		for (j=0 ; j<size ; j++)
		{
			plateau[i][j].color = buffer[j];
			plateau[i][j].appartenance =0;
		}
		fseek(file, 1, SEEK_CUR);
	}

	close_file(file);
	plateau[0][0].appartenance=1;

	return plateau;
}

void close_file(FILE* file)
{
	fclose(file);
}

int end_of_file(FILE* file)
{
	return feof(file);
}