#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grille.h"



grille initialize(int size)
{
	int i;
	grille plateau = NULL;
	plateau = (grille) calloc(size, sizeof(element *));
	for (i=0 ; i<size ; i++)
	{
		plateau[i] = (element *) calloc(size, sizeof(element));
	}

	return plateau;
}

void display(grille plateau, int size)
{
	int i, j;
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			printf("%2c", plateau[i][j].color);
		}
		printf("\n");
	}
}

grille random(int size)
{
	int i, j, k;
	grille plateau = initialize(size);
	srand(time(NULL));
	
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			k = rand() % 6;
			switch (k)
			{
				case 0:
				plateau[i][j].color = 'B';
				break;

				case 1:
				plateau[i][j].color = 'V';
				break;

				case 2:
				plateau[i][j].color = 'R';
				break;

				case 3:
				plateau[i][j].color = 'J';
				break;

				case 4:
				plateau[i][j].color = 'M';
				break;

				case 5:
				plateau[i][j].color = 'G';
				break;
			}
			plateau[i][j].appartenance=0;
		}
	}
	return plateau;
}

grille change_color(int i, int j, char c, grille plateau)
{
	plateau[i][j].color = c;
	return plateau;
}

bool if_flood(grille plateau, int size)
{     
	int i, j; 
	bool res = 1;
	for(i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{   
			if(plateau[0][0].color != plateau[i][j].color)
			{
				res = 0;
				j = size;
				i = size;
			}
		}
	}
	return res;
}

void free_space(grille plateau, int size)
{
	int i;
	for (i=0 ; i<size ; i++)
	{
		free(plateau[i]);
	}
	free(plateau);
}

