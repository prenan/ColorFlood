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
int solveur_arbre(SDL_Surface *ecran,node* root, grille plateau, int size, int nbr_coups)
{
	int a=0,b=0,c=0,d=0,e=0,f=0;
	int i;
	char* couleurs = "BVRJMG";
	grille plateau_test=initialize(size);
	while (if_flood(plateau,size)!=1)
	{
		for (i=0; i<6; i++)
		{
			plateau_test = copie(plateau, size);
			modif_color(couleurs[i], plateau_test, size);
			node_insert(root, plateau_test, couleurs[i]);
			display_SDL(ecran, plateau_test, size);
		}
		rootchild1= root;
		a=solveur_arbre(ecran, root->child1, root->child1->plateau, size, nbr_coups+1);
		b=solveur_arbre(ecran, root->child2, root->child2->plateau, size, nbr_coups+1);
		c=solveur_arbre(ecran, root->child3, root->child3->plateau, size, nbr_coups+1);
		d=solveur_arbre(ecran, root->child4, root->child4->plateau, size, nbr_coups+1);
		e=solveur_arbre(ecran, root->child5, root->child5->plateau, size, nbr_coups+1);
		f=solveur_arbre(ecran, root->child6, root->child6->plateau, size, nbr_coups+1);
	}
	return a;
}


	*/