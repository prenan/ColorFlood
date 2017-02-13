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
/* NE FONCTIONNE PAS ENCORE
int size_file(char* file_name)
{
	int size, nb_char = 0, nb_char_line1 = 0, nb_lines = 1;
	char text[601];
	FILE* file;
	file = open_file(file_name);

	fgets(text, 601, file);

	while (text[nb_char] != '\0')
	{
		if (text[nb_char] == '\n')
		{
			nb_lines = nb_lines+1;
		}
		while (text[nb_char] != '\n')
		{
			nb_char_line1 = nb_char_line1+1;
		}
		nb_char = nb_char+1;
	}

	if ((nb_char_line1 + 1)*nb_lines == nb_char)
	{
		size = nb_char_line1;
	}

	if (size == -1)
	{
		printf("contenu du fichier %s erroné\n", file_name);
		exit(1);
	}

	return size;
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

	/*close_file(file); NE FONCTIONNE PAS*/

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
