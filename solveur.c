#include "solveur.h"

char* solution(grille plateau, int size, int *nbr_coups)
{
	char* chemin=malloc(sizeof(char));
	*nbr_coups = 0;
	int i;
	char* couleurs = "BVRJMG";
	char ancienne_couleur = plateau[0][0];
	while(if_flood(plateau, size)==0)
	{
		i%=6;
		if (plateau[0][0] != couleurs[i])	
		{
			modif_color (0,0, couleurs[i], ancienne_couleur, plateau, size);
			chemin[*nbr_coups]=couleurs[i];
			i++;
		}
		else
		{
			i++;
			modif_color (0,0, couleurs[i], ancienne_couleur, plateau, size);
			chemin[*nbr_coups]=couleurs[i];
		}
		*nbr_coups = *nbr_coups +1;
	}
	*nbr_coups =*nbr_coups+2;
	return chemin;
}

/*
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
/*
char* solveur(grille plateau, int size, int* nbr_coups,char* chemin)
{
	*nbr_coups = 0;
	char * chemins[6]={chemin};
	char* couleurs = "BVRJMG";
	int i,j;
	grille plateau_test=initialize(size);
	coordonnee position={0,0};
	char ancienne_couleur = plateau[0][0];

	for (i=0; i<6; i++)
	{
		for(j=0; j<6; j++)
		{
			plateau_test=copie(plateau, size);
			modif_color (position, couleurs[j],ancienne_couleur, plateau_test, size);
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
	char ancienne_couleur = plateau[0][0];
	for (i=0; i<taille; i++)
	{
		modif_color(0,0,chemin[i], ancienne_couleur,plateau,size);
		ancienne_couleur = chemin[i];
	}
	return if_flood(plateau,size);
}

char* copie_texte(char* chemin, char* couleur)
{
	char *result = malloc(strlen(chemin)+strlen(couleur)+1);
	strcpy(result, chemin);
	strcat(result, couleur);
	return result;
}

char* solveur(grille plateau, int size, int *nbr_coups)
{
	int i,j,m=0,k=0;
	char* couleurs[6] = {"B","V","R","J","M","G"};
	char*** chemins=malloc(100*sizeof(char**));
	grille sol_plateau=initialize(size);

	for (i=0;i<100;i++)
	{
		chemins[i]=malloc(pow(5,i+1)*sizeof(char*));
	}

	for(i=0;i<6;i++)
	{
		if(couleurs[i][0]!=plateau[0][0])
		{
			chemins[0][k]=couleurs[i];
			k++;
		}
	}
	k=0;
	while(1)
	{
		for(i=0; i<pow(5,k+1);i++)
		{
			for (j=0;j<6;j++)
			{
				if(couleurs[j][0]!=chemins[k][i][k])
				{
					sol_plateau = copie(plateau,size);
					chemins[k+1][m+i*5]=copie_texte(chemins[k][i],couleurs[j]);
					if(testeur_chemins(chemins[k+1][m+i*5],sol_plateau,size)==1)
					{
						*nbr_coups = k+2;
						return chemins[k+1][m+i*5];			
					}
					m++;
				}
			}
			m=0;
		}
		k++;
	}
	return 0;
}