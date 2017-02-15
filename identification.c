#include <stdio.h>
#include <stdlib.h>

#include "pile.h"
#include "grille.h"


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
		res = empiler(res, fils_gauche);
	}

	if ( j != size && (plateau[i][j+1].color == c || plateau[i][j+1].color == couleur_choisie) )
	{
		res = empiler(res, fils_droite);
	}

	if ( i != 0 && (plateau[i-1][j].color == c || plateau[i-1][j].color == couleur_choisie) )
	{
		res = empiler(res, fils_haut);
	}

	if ( i != size && (plateau[i+1][j].color == c || plateau[i+1][j].color == couleur_choisie) )
	{
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
		depiler(pile_des_fils); /* on la supprime de pile_des_fils */

		pile_des_fils = extraire_fils(pere, pile_des_fils, couleur_choisie, plateau, size); /* on n'oublie pas d'extraire de ce "père" anciennement "fils" de nouveaux fils éventuels */
	}

	return resultat;
}