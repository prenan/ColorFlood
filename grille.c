#include "grille.h"
#include "coordonnees.h"


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
			plateau[i][j].appartenance = 0;
		}
	}
	plateau[0][0].appartenance=1;
	return plateau;
}

grille change_color(coordonnees coord, char c, grille plateau)
{
	int i=coord.x;
	int j=coord.y;
	
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

int test_neighbour(grille plateau, coordonnees coord, int size, char couleur_choisie)
{
	int i=coord.x, j=coord.y,voisin=1;
	if (i<0 || j<0 || i>size || j>size)
	{
		perror("Erreur coordonnees");
		exit(1);
	}
	switch(voisin)
	{
		case 1:
		{
			if (i!=0 && plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				break;
			else
				voisin++;
		}
		case 2:
		{
			if (j!= size-1 && plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				break;
			else
				voisin++;
		}
		case 3:
		{
			if (i!=size-1 && plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				break;
			else
				voisin++;
		}
		case 4:
		{
			if (j!= 0 && plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				break;
			else
				voisin=0;
		}
	}
	return voisin;
}

void modif_color(char couleur_choisie, grille plateau, int size)
{
	coordonnees position;

	Pile P = NULL;

	int i,j;

	for (i=0 ; i<size ;i++)
	{
		for (j=0 ; j<size ; j++)
		{
			position= coord_def(i, j);
			if(plateau[i][j].appartenance==1)
			{
				change_color(position,couleur_choisie,plateau);
				P=empiler(P,position);
				while(pile_estVide(P)!=1)
				{
					position = P->tete; 
					P=Deep(couleur_choisie, plateau, size, position, P);
					P=depiler(P);
				}
			}
		}
	}
	free(P);
}

Pile Deep(char couleur_choisie, grille plateau, int size, coordonnees position_pere, Pile P)
{
	coordonnees position_fils;
	switch (test_neighbour(plateau, position_pere, size, couleur_choisie))
	{
		case 0:
		break;
		case 1:
		{
			position_fils = coord_def(position_pere.x-1 , position_pere.y);
			plateau[position_fils.x][position_fils.y].appartenance = 1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 2:
		{
			position_fils = coord_def(position_pere.x, position_pere.y+1);
			plateau[position_fils.x][position_fils.y].appartenance=1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 3:
		{
			position_fils = coord_def(position_pere.x+1, position_pere.y);
			plateau[position_fils.x][position_fils.y].appartenance = 1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 4:
		{
			position_fils = coord_def(position_pere.x, position_pere.y-1);
			plateau[position_fils.x][position_fils.y].appartenance = 1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}
	}
	return P;
}
