/**
 * \file pile.h
 * \brief Fonctions sur les piles et définition de structures
 * \author THOR
 * \date février 2017
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef PILE_H
#define PILE_H

/**
 * \struct coordonnees
 * \brief Structure d'une case du plateau
 *
 * Pour une case, on a sa position sur le plateau (x pour la ligne, j pour la colonne),
 * (0, 0) correspond à la case dans le coin en-haut à gauche du plateau.
 */
typedef struct coordonnees
{
	int x;
	int y;
} coordonnees;

/**
 * \struct liste
 * \brief Structure d'une liste
 *
 * Une liste est définie par un élément en tête (ici une case donc de type coordonnees),
 * ainsi que par son reste.
 */
typedef struct liste
{
    coordonnees tete;
    struct liste *suivant;
} Cellule, *Pile;


/**
 * \fn Pile pile_initialiser()
 * \brief Fonction d'initialisation d'une pile.
 *
 * \return NULL.
 */
Pile pile_initialiser();


/*test pile vide ou pleine vrai = 1, faux = 0*/
int pile_estVide(Pile P);


/* Empiler : ajout d'un élément au sommet */
Pile empiler(Pile P, coordonnees elem);


/* Depiler : la fonction permet de supprimer le sommet et le récupérer dans une autre variable */
Pile depiler(Pile P);

/* vider la pile et détruire la liste pour libérer la mémoire */ 
void pile_vider(Pile P);

/* la taille de la pile */ 
int pile_taille(Pile P);

/*affichage*/
void pile_affichage(Pile P);


#endif
