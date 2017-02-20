#include "fichier.h"


int open_file(char const* file_name)
{
	int file_in;
	file_in = open(file_name, O_RDONLY);
	if (-1 == file_in) 
	{
		perror("problème d'ouverture de fichier");
		exit(1);
	}
	return file_in;
}

void close_file(int file_in)
{
	close(file_in);
}

int size_file(char* file_name)
{
	int file_in, n, size, nb_char = 0, nb_char_line1 = 0, nb_lines = 1;
	char text[601];

	file_in = open_file(file_name);
	n = read(file_in, text, 601);

	if (-1 == n)
	{
		perror("problème de lecture de fichier");
	}

	while (text[nb_char] != '\n')	/*compte le nb de caractères sur la 1ère ligne*/
	{
		nb_char_line1++;
		nb_char++;
	}

	while (text[nb_char])	/*compte le nb de caractères au total (sans le \0)
									et le nb de lignes*/
	{
		if (text[nb_char] == '\n')
		{
			nb_lines++;
		}
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
	int i, j, k = 0, file_in, r;
	char text[601];

	file_in = open_file(file_name);
	r = read(file_in, text, 601);

	if (-1 == r)
	{
		perror("problème de lecture de fichier");
	}

	grille plateau = initialize(size);
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			plateau[i][j].color = text[i*size + j + k];	/*le k sert à sauter les \n*/
			plateau[i][j].appartenance = 0;
		}
		k++;
	}

	close_file(file_in);
	plateau[0][0].appartenance = 1;

	return plateau;
}

void export_file(grille plateau, int size)
{
	int i, j;
	FILE * file_out = fopen("plateau.txt", "w");

	if (!file_out)
	{
		perror("problème d'écriture de fichier");
		exit(1);
	}

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			fputc(plateau[i][j].color, file_out);	/*caractère par caractère*/
			if (j == size-1 && i != size-1)
			{
				fputc('\n', file_out);	/*pour mettre les \n en bout de ligne sauf la dernière*/
			}
		}
	}
	fclose(file_out);
}