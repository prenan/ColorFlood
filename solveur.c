#include "solveur.h"

int solution(grille plateau, int size)
{
	int nbr_coups = 0, i;
	char* couleurs = "BVRJMG";
	while(if_flood(plateau, size)==0)
	{
		if (plateau[0][0].color != couleurs[i])	
		{
			modif_color (couleurs[i], plateau, size);
			i++;
		}
		else
		{
			i++;
			modif_color (couleurs[i], plateau, size);
		}
		nbr_coups ++;
		i%=6;
	}
	return nbr_coups;
}


int solution_opti(grille plateau, int size)
{
	int nbr_coups = 0, i,max=0,place;
	grille plateau_test=initialize(size);
	char* couleurs = "BVRJMG";
	int valeur[6];
	while(if_flood(plateau, size)!=1)
	{
		for (i=0; i<6; i++)
		{
			plateau_test=copie(plateau, size);
			modif_color (couleurs[i], plateau_test, size);
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
		modif_color(couleurs[place],plateau,size);
		nbr_coups ++;
		i%=6;
	}
	return nbr_coups;
}
int compteur_appartenance(grille plateau, int size)
{
	int i, j, compteur=0;
	for (i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			compteur += plateau[i][j].appartenance;
		}
	}
	return compteur;
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