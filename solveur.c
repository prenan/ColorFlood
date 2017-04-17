#include "solveur.h"


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

void comparateur_avancement(grille plateau, int size,int* valeur)
{
	char* couleurs = "BVRJMG";
	char ancienne_couleur = plateau[0][0];
	int i, j, k;
	for (i=0 ; i<6 ; i++)
	{
		valeur[i] = 0;
		grille testeur = copie(plateau, size);
		modif_color(0, 0, couleurs[i], ancienne_couleur, testeur, size);
		modif_color(0, 0, 'C', couleurs[i], testeur, size);
		for(j=0 ; j<size ; j++)
		{
			for (k=0 ; k<size ; k++)
			{
				if( testeur[j][k] == 'C')
				{
					valeur[i]++;
				}
			}
		}
		free_space(testeur,size);
	}
}
int minimum(int* valeur)
{
	int i,mini=valeur[0];
	for(i=1 ; i<6 ; i++)
	{
		if(valeur[i]<mini)
			mini = valeur[i];
	}
	return mini;
}

void free_c(char** chemins,int k)
{
	int i;
	for (i=0 ; i<k ; i++)
	{
		free(chemins[i]);
		chemins[i] = NULL;
	}
	free(chemins);
	chemins = NULL;
}

char* solveur_perf(grille plateau, int size, int *nbr_coups_min)
{
	time_t deb, fin; 
	time(&deb);
	int i, j, k = 0, l = 0, min;
	char* couleurs[6] = {"B\0", "V\0", "R\0", "J\0", "M\0", "G\0"};
	char** chemins_1 = malloc(5*sizeof(char*));
	char** chemins_2 = malloc(5*sizeof(char*));
	grille sol_plateau = NULL;
	int valeur[6]={0};

	comparateur_avancement(plateau,size,valeur);
	min = minimum(valeur);
	for(i=0 ; i<6 ; i++)
	{
		if(valeur[i]>min)
		{
			chemins_1[k] = couleurs[i];
			k++;
		}
	}
	while(1)
	{
		chemins_2 = realloc(chemins_2,5*k*sizeof(char*));
		for(i=0 ; i<k ; i++)
		{
			sol_plateau = copie(plateau, size);
			testeur_chemins(sol_plateau,size, chemins_1[i]);
			comparateur_avancement(sol_plateau,size,valeur);
			min= minimum(valeur);
			for (j=0 ; j<6 ; j++)
			{
				if(valeur[j]>min)
				{
					sol_plateau = copie(plateau, size);
					chemins_2[l] = concatener(chemins_1[i], couleurs[j]);
					/*printf("%s\n", chemins_2[l]); */ //utile pour les tests
					if(testeur_chemins(sol_plateau, size, chemins_2[l]) == 1)
					{
						char* solution = chemins_2[l];
						*nbr_coups_min = strlen(solution);
						free_c(chemins_1,k);
						free_c(chemins_2,l);
						free_space(sol_plateau, size);
						time(&fin); 
						printf("Le solveur a mis %lu seconde(s).\n", fin - deb); 
						return solution;			
					}
					free_space(sol_plateau, size);
					l++;
				}
			}
		}
		chemins_1 = realloc(chemins_1,l*sizeof(char*));
		for(j=0 ; j<l ; j++)
		{
			chemins_1[j] = chemins_2[j];
		}
		k=l;
		l=0;
	}
	return 0;
}

char* solution_rapide(grille plateau, int size, int *nbr_coups)
{	
	char* chemin = malloc(100*sizeof(char));
	*nbr_coups = 0;
	int i, max=0, place;
	char* couleurs = "BVRJMG";
	int valeur[6]={0};
	char ancienne_couleur = plateau[0][0];
	while(if_flood(plateau, size)==0)
	{
		grille plateau_test=copie(plateau,size);
		comparateur_avancement(plateau_test, size, valeur);

		for(i=0; i<6; i++)
		{
			if(valeur[i]>max)
			{
				max=valeur[i];
				place=i;
			}
		}
		chemin[*nbr_coups]=couleurs[place];
		modif_color(0,0, couleurs[place], ancienne_couleur,plateau,size);
		ancienne_couleur = couleurs[place];
		*nbr_coups =*nbr_coups+1;
		free_space(plateau_test,size);
	}
	return chemin;
}