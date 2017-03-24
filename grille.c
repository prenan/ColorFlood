#include "grille.h"


int choose_size()
{
	int size; 
	printf("Entrer la taille du jeu (entre 4 et 24) :\n"); 
	scanf("%d", &size); 
	while(size<4 || size>24) 
	{ 
		printf("La taille doit être comprise entre 4 et 24.\n"); 
		scanf("%d", &size); 
	} 
	return size;
}

grille initialize(int size)
{
	int i;
	grille plateau = NULL;
	plateau = (grille) calloc(size, sizeof(char *));
	for (i=0 ; i<size ; i++)
	{
		plateau[i] = (char *) calloc(size, sizeof(char));
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
			printf("%2c", plateau[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

grille random_grille(int size)
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
				plateau[i][j] = 'B';
				break;

				case 1:
				plateau[i][j] = 'V';
				break;

				case 2:
				plateau[i][j] = 'R';
				break;

				case 3:
				plateau[i][j] = 'J';
				break;

				case 4:
				plateau[i][j] = 'M';
				break;

				case 5:
				plateau[i][j] = 'G';
				break;
			}
		}
	}
	return plateau;
}

grille change_color(coordonnees coord, char c, grille plateau)
{
	int i=coord.x;
	int j=coord.y;

	plateau[i][j] = c;

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
			if(plateau[0][0] != plateau[i][j])
			{
				return res = 0;
			}
		}
	}
	return res;
}

void free_space(grille plateau, int size)
{
	int i;
	for (i=0; i<size; i++)
	{
		free(plateau[i]);
		plateau[i] = NULL;
	}
	free(plateau);
	plateau = NULL;
}

void modif_color(coordonnees position, char couleur_choisie, char ancienne_couleur, grille plateau, int size)
{
	int x=position.x;
	int y=position.y;
	coordonnees new_position=coord_def(x,y);

	if(plateau[x][y] == ancienne_couleur)
	{
		printf("choix %c\n",couleur_choisie );
		printf("ancienne %c\n",ancienne_couleur );
		printf("0\n");
		plateau[x][y] = couleur_choisie;
		if(x+1 < size)
		{
			new_position.x = position.x+1 ;
			printf("position x %d\n",position.x);
			printf("position y %d\n",position.y);
			modif_color(new_position, couleur_choisie, ancienne_couleur, plateau, size);	
			printf("1\n");
		}
		if(x-1 >= 0)
		{
			new_position.x = position.x-1;
			printf("position x %d\n",position.x);
			printf("position y %d\n",position.y);
			modif_color(new_position, couleur_choisie, ancienne_couleur, plateau, size);	
			printf("2\n");
		}
		if(y+1 < size)
		{
			new_position.y = position.y+1;
			printf("position x %d\n",position.x);
			printf("position y %d\n",position.y);
			modif_color(new_position, couleur_choisie, ancienne_couleur, plateau, size);	
			printf("3\n");
		}
		if(y-1 >= 0)
		{
			new_position.y = position.y-1;
			printf("position x %d\n",position.x);
			printf("position y %d\n",position.y);
			modif_color(new_position, couleur_choisie, ancienne_couleur, plateau, size);	
			printf("4\n");
		}
	}
}

grille copie(grille plateau, int size)
{
	int i, j;
	grille new_plateau=initialize(size);
	for (i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			new_plateau[i][j]=plateau[i][j];
		}
	}
	return new_plateau;
}