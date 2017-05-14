#include "solveur.h"


// @brief compute time difference in seconds
static
double timeval_diff(struct timeval tv1, struct timeval tv2)
{
	return (tv2.tv_sec-tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec)*1E-6;
}

char* concatener(char* chemin, char* couleur)
{
	char* result = malloc(strlen(chemin)+strlen(couleur)+1);
	strcpy(result, chemin);
	strcat(result, couleur);
	return result;
}

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

void comparateur_avancement(grille plateau, int size, int* valeur)
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
				if(testeur[j][k] == 'C')
				{
					valeur[i]++;
				}
			}
		}
		free_space(testeur,size);
	}
}

int couleurs_restantes(grille plateau, int size)
{
	int i, j, nb_couleur = 0;
	int valeur[6]={0};
	for (i=0 ; i < size ; i++)
	{
		for (j=0 ; j < size ; j++)
		{
			if( plateau[i][j] == 'B')
				valeur[0]=1;
			else if( plateau[i][j] == 'V')
				valeur[1]=1;
			else if( plateau[i][j] == 'R')
				valeur[2]=1;
			else if( plateau[i][j] == 'J')
				valeur[3]=1;
			else if( plateau[i][j] == 'M')
				valeur[4]=1;
			else if( plateau[i][j] == 'G')
				valeur[5]=1;
		}
	}
	for (i=0 ; i < 6 ; i++)
		nb_couleur += valeur[i];
	return nb_couleur;
}

void comparateur_avancement2(grille plateau, int size, int* valeur, int ancien_nb_couleur)
{
	char* couleurs = "BVRJMG";
	char ancienne_couleur = plateau[0][0];
	int i, j, k, nb_couleur;
	for (i=0 ; i<6 ; i++)
	{
		valeur[i] = 0;
		grille testeur = copie(plateau, size);
		modif_color(0, 0, couleurs[i], ancienne_couleur, testeur, size);
		modif_color(0, 0, 'C', couleurs[i], testeur, size);
		nb_couleur = couleurs_restantes(testeur, size);
		if (nb_couleur >= ancien_nb_couleur)
		{
			for(j=0 ; j<size ; j++)
			{
				for (k=0 ; k<size ; k++)
				{
					if(testeur[j][k] == 'C')
					{
						valeur[i]++;
					}
				}
			}
		}
		free_space(testeur,size);
	}
}

int minimum(int* tableau)
{
	int i, mini = tableau[0];
	for(i=1 ; i<6 ; i++)
	{
		if(tableau[i]<mini)
			mini = tableau[i];
	}
	return mini;
}

char* solution_rapide(grille plateau, int size, int *nbr_coups)
{	
	int i, max = 0, place, valeur[6] = {0};
	char *chemin = malloc(100*sizeof(char));
	char *couleurs = "BVRJMG", ancienne_couleur = plateau[0][0];
	*nbr_coups = 0;

	while (!if_flood(plateau, size))
	{
		grille plateau_test = copie(plateau, size);
		comparateur_avancement(plateau_test, size, valeur);

		for (i=0; i<6; i++)
		{
			if (valeur[i]>max)
			{
				max=valeur[i];
				place=i;
			}
		}
		chemin[*nbr_coups] = couleurs[place];
		modif_color(0,0, couleurs[place], ancienne_couleur, plateau, size);
		ancienne_couleur = couleurs[place];
		*nbr_coups = *nbr_coups+1;
		free_space(plateau_test, size);
	}
	return chemin;
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

char* solveur_perf(grille plateau, int size, int *nbr_coups_min)
{
	int i, j, k = 0, l = 0, min, valeur[6]={0};
	char* couleurs[6] = {"B\0", "V\0", "R\0", "J\0", "M\0", "G\0"};
	char** chemins_1 = malloc(5*sizeof(char*));
	char** chemins_2 = malloc(sizeof(char*));
	grille sol_plateau = NULL;

	modif_color(0, 0, 'C', plateau[0][0], plateau, size);
	int nb_couleur =  couleurs_restantes(plateau, size);
	struct timeval deb, fin;
	gettimeofday(&deb, 0);
	comparateur_avancement2(plateau, size, valeur, nb_couleur);
	min = minimum(valeur);
	if (min != 0)
	{
		for (i=0 ; i<6 ; i++)
		{
			if (valeur[i]>min)
			{
				chemins_1[k] = couleurs[i];
				sol_plateau = copie(plateau, size);
				if (testeur_chemins(sol_plateau, size, chemins_1[k]) == 1)
				{
					char* solution = chemins_1[k];
					*nbr_coups_min = strlen(solution);
					free_c(chemins_1,k);
					free_c(chemins_2,l);
					free_space(sol_plateau, size);
					gettimeofday(&fin, 0);
					printf("Le solveur a mis %g seconde(s).\n", timeval_diff(deb, fin)); 
					return solution;
				}
				free_space(sol_plateau, size);
				k++;
			}
		}
	}
	else
	{
		for (i=0 ; i < 6 ; i++)
		{
			if (valeur[i] == 0)
			{
				chemins_1[0] = couleurs[i];
				sol_plateau = copie(plateau, size);
				if (testeur_chemins(sol_plateau, size, chemins_1[0]) == 1)
				{
					char* solution = chemins_1[0];
					*nbr_coups_min = strlen(solution);
					free_c(chemins_1,0);
					free_c(chemins_2,l);
					free_space(sol_plateau, size);
					gettimeofday(&fin, 0);
					printf("Le solveur a mis %g seconde(s).\n", timeval_diff(deb, fin)); 
					return solution;
				}
				k++;
				i=6;
			}
		}
	}
	while(1)
	{
		chemins_2 = realloc(chemins_2, 5*k*sizeof(char*));
		for (i=0 ; i<k ; i++)
		{
			sol_plateau = copie(plateau, size);
			testeur_chemins(sol_plateau,size, chemins_1[i]);
			modif_color(0, 0, 'C', sol_plateau[0][0], sol_plateau, size);
			nb_couleur = couleurs_restantes(sol_plateau,size);
			comparateur_avancement2(sol_plateau, size, valeur, nb_couleur);
			min = minimum(valeur);
			if(min != 0)
			{
				for (j=0 ; j<6 ; j++)
				{
					if (valeur[j]>min)
					{
						sol_plateau = copie(plateau, size);
						chemins_2[l] = concatener(chemins_1[i], couleurs[j]);	
						//printf("%s\n", chemins_2[l]);  utile pour les tests
						if (testeur_chemins(sol_plateau, size, chemins_2[l]) == 1)
						{
							char* solution = chemins_2[l];
							*nbr_coups_min = strlen(solution);
							free_c(chemins_1, k-1);
							free_c(chemins_2, l);
							free_space(sol_plateau, size);
							gettimeofday(&fin, 0);
							printf("Le solveur a mis %g seconde(s).\n", timeval_diff(deb, fin)); 
							return solution;
						}
						free_space(sol_plateau, size);
						l++;
					}
				}
			}
			else
			{
				for (j=0 ; j<6 ; j++)
				{
					if (valeur[j] == 0)
					{
						sol_plateau = copie(plateau, size);
						chemins_2[l] = concatener(chemins_1[i], couleurs[j]);
						if (testeur_chemins(sol_plateau, size, chemins_2[l]) == 1)
						{
							char* solution = chemins_2[l];
							*nbr_coups_min = strlen(solution);
							free_c(chemins_1, k-1);
							free_c(chemins_2, l);
							free_space(sol_plateau, size);
							gettimeofday(&fin, 0);
							printf("Le solveur a mis %g seconde(s).\n", timeval_diff(deb, fin)); 
							return solution;
						}
						free_space(sol_plateau, size);
						l++;
						j=6;
					}
				}
			}
		}
		chemins_1 = realloc(chemins_1, l*sizeof(char*));
		for (j=0 ; j<l ; j++)
		{
			chemins_1[j] = chemins_2[j];
		}
		k = l;
		l = 0;
	}
	return 0;
}


void free_c(char** chemins, int k)
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