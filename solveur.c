#include "solveur.h"


/*
//Solution du jeu mais pas la minimale
char* solution_opti(grille plateau, int size, int *nbr_coups)
{
	char* chemin=malloc(sizeof(char));
	*nbr_coups = 0;
	int i,max=0,place;
	grille plateau_test=initialize(size);
	char* couleurs = "BVRJMG";
	int valeur[6];
	coordonnees position={0,0};
	char ancienne_couleur = plateau[0][0];
	while(if_flood(plateau, size)!=1)
	{
		for (i=0; i<6; i++)
		{
			plateau_test=copie(plateau, size);
			modif_color (position, couleurs[i], ancienne_couleur, plateau_test, size);
			valeur[i]=compteur_appartenance(plateau_test, size);
		}
		for(i=0; i<6; i++)
		{
			if(valeur[i]>max)
			{
				max=valeur[i];
				place=i;
			}
		}
		chemin[*nbr_coups]=couleurs[place];
		modif_color(position, couleurs[place], ancienne_couleur,plateau,size);
		*nbr_coups =*nbr_coups+1;
	}
	free_space(plateau_test,size);
	return chemin; 
}*/

bool testeur_chemins(grille plateau, int size, char* chemin)
{
	int i, taille = strlen(chemin);
	char ancienne_couleur = plateau[0][0];
	for (i=0 ; i<taille ; i++)
	{
		modif_color(0, 0, chemin[i], ancienne_couleur, plateau, size);
		ancienne_couleur = chemin[i];
	}
	return if_flood(plateau, size);
}

char* concatener(char* chemin, char* couleur)
{
	char* result = malloc(strlen(chemin)+strlen(couleur)+1);
	strcpy(result, chemin);
	strcat(result, couleur);
	return result;
}

char* solveur_brut(grille plateau, int size, int *nbr_coups_min)
{
	int i, j, m = 0, k = 0, l;
	char* couleurs[6] = {"B", "V", "R", "J", "M", "G"};
	char*** chemins = malloc(100*sizeof(char**));
	grille sol_plateau = NULL;

	for (i=0 ; i<100 ; i++)
	{
		chemins[i] = malloc(pow(5,i+1)*sizeof(char*));
	}

	for(i=0 ; i<6 ; i++)
	{
		if(couleurs[i][0] != plateau[0][0])
		{
			chemins[0][k] = malloc(sizeof(char));
			chemins[0][k] = couleurs[i];
			k++;
		}
	}
	k = 0;
	while(1)
	{
		for(i=0 ; i<pow(5,k+1) ; i++)
		{
			for (j=0 ; j<6 ; j++)
			{
				if(couleurs[j][0] != chemins[k][i][k])
				{
					sol_plateau = copie(plateau, size);
					l = m + i*5;
					chemins[k+1][l] = concatener(chemins[k][i], couleurs[j]);
					if(testeur_chemins(sol_plateau, size, chemins[k+1][l]) == 1)
					{
						*nbr_coups_min = k+2;
						char* solution = chemins[k+1][l];
						free_space(sol_plateau, size);
						free_chemins(chemins, i, j, k, l);
						return solution;			
					}
					free_space(sol_plateau, size);
					m++;
				}
			}
			m = 0;
		}
		k++;
	}
	return 0;
}

void free_chemins(char*** chemins, int i, int j, int k, int l)
{
	for(i=0 ; i<100 ; i++)
	{
		if(i>0 && i<k+1)
		{
			for(j=0 ; j<pow(5,i+1) ; j++)
			{
				free(chemins[i][j]);
				chemins[i][j] = NULL;
			}
		}
		if(i == k+1)
		{
			for(j=0 ; j<l ; j++)
			{
				free(chemins[i][j]);
				chemins[i][j] = NULL;
			}
		}
		free(chemins[i]);
		chemins[i] = NULL;
	}
	free(chemins);
	chemins = NULL;
}