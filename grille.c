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
	for (i=0 ; i<size ; i++)
	{
		free(plateau[i]);
	}
	free(plateau);
}

int test_neighbour(grille plateau, coordonnees coord, int size, char couleur_choisie)
{
	int test=0;
	int i=coord.x;
	int j=coord.y;
	if (i<0||j<0||i>size||j>size)
	{
		perror("Erreur coordonnees");
		exit(1);
	}
	if (i!=0 && i!=size-1 && j!=0 && j!= size-1)
	{
		if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
			test=1;

		if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
			test=2;

		if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
			test=3;

		if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
			test=4;
	}
	if (i==0)
	{
		if (j==0)
		{
			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;
		}
		if (j==size-1)
		{
			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
		if(j!=0 && j!= size-1)
		{
			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
	}
	if (i==size-1)
	{
		if (j==0)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;
		}
		if (j==size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
		if (j !=0 && j!= size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
	}
	if (j==0)
	{
		if (i==0)
		{
			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;
		}
		if (i==size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;
		}
		if (i!=0 && i!= size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i][j+1].appartenance==0 && plateau[i][j+1].color==couleur_choisie)
				test=2;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;
		}
	}
	if (j==size-1)
	{
		if(i==0)
		{
			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
		if(i==size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
		if (i!=0 && i!=size-1)
		{
			if(plateau[i-1][j].appartenance==0 && plateau[i-1][j].color==couleur_choisie)
				test=1;

			if(plateau[i+1][j].appartenance==0 && plateau[i+1][j].color==couleur_choisie)
				test=3;

			if(plateau[i][j-1].appartenance==0 && plateau[i][j-1].color==couleur_choisie)
				test=4;
		}
	}
	return test;
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
			position.x = i; 
			position.y = j;
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
			position_fils.x = position_pere.x-1;
			position_fils.y = position_pere.y;
			plateau[position_fils.x][position_fils.y].appartenance = 1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 2:
		{
			position_fils.x = position_pere.x;
			position_fils.y = position_pere.y+1;
			plateau[position_fils.x][position_fils.y].appartenance=1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 3:
		{
			position_fils.x = position_pere.x+1;
			position_fils.y = position_pere.y;
			plateau[position_fils.x][position_fils.y].appartenance = 1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}

		case 4:
		{
			position_fils.x = position_pere.x;
			position_fils.y = position_pere.y-1;
			plateau[position_fils.x][position_fils.y].appartenance = 1;
			P = empiler(P,position_fils);
			P = Deep(couleur_choisie, plateau, size, position_fils, P);
			break;
		}
	}
	return P;
}