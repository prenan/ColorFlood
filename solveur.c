#include "solveur.h"

char* solution(grille plateau, int size, int *nbr_coups)
{
	char* chemin=malloc(sizeof(char));
	*nbr_coups = 0;
	int i;
	char* couleurs = "BVRJMG";
	while(if_flood(plateau, size)==0)
	{
		if (plateau[0][0].color != couleurs[i])	
		{
			modif_color (couleurs[i], plateau, size);
			chemin[*nbr_coups]=couleurs[i];
			i++;
		}
		else
		{
			i++;
			modif_color (couleurs[i], plateau, size);
			chemin[*nbr_coups]=couleurs[i];
		}
		*nbr_coups = *nbr_coups +1;
		i%=6;
	}
	*nbr_coups =*nbr_coups+2;
	return chemin;
}


char* solution_opti(grille plateau, int size, int *nbr_coups)
{
	char* chemin=malloc(sizeof(char));
	*nbr_coups = 0;
	int i,max=0,place;
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
		chemin[*nbr_coups]=couleurs[place];
		modif_color(couleurs[place],plateau,size);
		*nbr_coups =*nbr_coups+1;
		i%=6;
	}
	free_space(plateau_test,size);
	*nbr_coups =*nbr_coups+2;
	return chemin; 
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
/*
char* solveur(grille plateau, int size, int* nbr_coups,char* chemin)
{
	*nbr_coups = 0;
	char * chemins[6]={chemin};
	char* couleurs = "BVRJMG";
	int i,j;
	grille plateau_test=initialize(size);


	for (i=0; i<6; i++)
	{
		for(j=0; j<6; j++)
		{
			plateau_test=copie(plateau, size);
			modif_color (couleurs[j], plateau_test, size);
			if(compteur_appartenance(plateau,size)!=compteur_appartenance(plateau_test,size))
			{
				chemins[i]=copie_texte(chemins[i],couleurs[j]);
				printf("%s\n",chemins[i] );
			}
			if(testeur_chemins(chemins[i],plateau,size)==1)
				return chemins[i];
			else
				solveur(plateau, size, nbr_coups,chemins[i]);
		}
	}
	free_space(plateau,size);
	return chemins[i];
}*/

int testeur_chemins(char* chemin, grille plateau, int size)
{
	int taille = strlen(chemin);
	int i;
	for (i=0; i<taille; i++)
	{
		modif_color(chemin[i],plateau,size);
	}
	return if_flood(plateau,size);
}

char* copie_texte(char* chemin, char couleur)
{
	char ajout[1]= {couleur};
	char *result = malloc(strlen(chemin)+strlen(ajout)+1);
	strcpy(result, chemin);
	strcat(result, ajout);
	return result;
}