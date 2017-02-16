#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grille.h"
#include "pile.h"


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
}

grille random(int size)
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
			plateau[i][j].appartenance=0;
		}
	}
	return plateau;
}

grille change_color(int i, int j, char c, grille plateau)
{
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
				res = 0;
				j = size;
				i = size;
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


Pile extraire_fils(coordonnees pere, Pile P, char couleur_choisie, grille plateau, int size) /* on met dans P tout "les fils" de "pere" */
{
	Pile res = P;

	int i = pere.x;
	int j = pere.y;
	char c = plateau[i][j].color;

	coordonnees fils_gauche, fils_droite, fils_haut, fils_bas;

	fils_gauche.x = i;
	fils_gauche.y = j-1;

	fils_droite.x = i;
	fils_droite.y = j+1;

	fils_haut.x = i-1;
	fils_haut.y = j;

	fils_bas.x = i+1;
	fils_bas.y = j;


	if ( j != 0 && (plateau[i][j-1].color == c || plateau[i][j-1].color == couleur_choisie) )
	{
		if (plateau[i][j-1].appartenance != 1)
			res = empiler(res, fils_gauche);
	}

	if ( j != size-1 && (plateau[i][j+1].color == c || plateau[i][j+1].color == couleur_choisie) )
	{
		if (plateau[i][j+1].appartenance != 1)
			res = empiler(res, fils_droite);
	}

	if ( i != 0 && (plateau[i-1][j].color == c || plateau[i-1][j].color == couleur_choisie) )
	{
		if (plateau[i-1][j].appartenance != 1)
			res = empiler(res, fils_haut);
	}

	if ( i != size-1 && (plateau[i+1][j].color == c || plateau[i+1][j].color == couleur_choisie) )
	{
		if (plateau[i+1][j].appartenance != 1)
			res = empiler(res, fils_bas);
	}

	return res;
}

Pile identifier_tache(grille plateau, char couleur_choisie, int size)
{
	Pile resultat, pile_des_fils;
	coordonnees pere;

	pere.x = 0; /* on initialise le pere à la case origine qui va donner naissance à tous les fils */
	pere.y = 0;

	resultat = pile_initialiser(); /* le résultat est une pile qui contient toutes les coordonnées des cases de la tâche connexe */

	pile_des_fils = pile_initialiser(); /* un fils représente un chemin possible */
	pile_des_fils = empiler(pile_des_fils, pere);

	while( !pile_estVide(pile_des_fils) )
	{
		pere = pile_des_fils->tete;

		(plateau[pere.x][pere.y]).appartenance = 1; /* on marque bien qu'on a visité cette case et qu'elle appartient dorénavant à la tache */
		resultat = empiler(resultat, pere); /* on la rajoute dans le resultat */
		pile_des_fils = depiler(pile_des_fils); /* on la supprime de pile_des_fils */

		pile_des_fils = extraire_fils(pere, pile_des_fils, couleur_choisie, plateau, size); /* on n'oublie pas d'extraire de ce "père" anciennement "fils" de nouveaux fils éventuels */
	}

	return resultat;
}