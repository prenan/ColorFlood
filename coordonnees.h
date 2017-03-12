/**
 * \file coordonnees.h
 * \brief Stucture de couple de coordonnées et fonctions de manipulation
 * 															 
 * \author THOR
 * \date février 2017
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef COORDONNEES_H
#define COORDONNEES_H


/**
 * \struct coordonnees
 * \brief représente les coordonnées d'une case du plateau
 *
 * Pour une case, on a sa position sur le plateau (x pour la ligne, y pour la colonne),
 * (0, 0) correspond à la case dans le coin supérieur gauche du plateau.
 */
typedef struct coordonnees
{
	int x;
	int y;
} coordonnees;

/**
 * \fn  coordonnees coord_def(int i, int j)
 * \brief définir un couple de coordonnées (i,j) 
 *
 * \param i la ligne
 * \param j la colonne
 * \return coordonnees A tq A.x = i et A.y = j.
 */
coordonnees coord_def(int i, int j);

/**
 * \fn  int coord_compare(coordonnees A, coordonnees B)
 * \brief tester l'égalité de deux couples de coordonnées   
 *
 * \return 1 si c'est le même couple, 0 sinon.
 */
int coord_compare(coordonnees A, coordonnees B);


#endif