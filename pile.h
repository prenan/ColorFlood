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

/**
 * \fn int pile_estVide(Pile P)
 * \brief Fonction de test pour savoir si la pile est vide.
 *
 * \param P la pile que l'on test.
 * \return 1 si elle est vide, 0 sinon.
 */
int pile_estVide(Pile P);


/**
 * \fn Pile empiler(Pile P, coordonnees elem)
 * \brief Fonction qui empile une coordonnée dans une pile.
 *
 * \param P la pile qui va être enpilée.
 * \param elem la coordonnée que l'on souaite empilée.
 * \return la pile avec le nouvel element en tête.
 */
Pile empiler(Pile P, coordonnees elem);

/**
 * \fn Pile depiler(Pile P)
 * \brief Fonction qui depile la pile.
 *
 * \param P la pile qui va être dépilée.
 * \return la pile avec un élément de moins.
 */
Pile depiler(Pile P);

/* vider la pile et détruire la liste pour libérer la mémoire */ 
void pile_vider(Pile P);

/**
 * \fn int pile_taille(Pile P)
 * \brief Fonction qui delivre la taille.
 *
 * \param P la pile dont on souhaite connaitre la taille.
 * \return la taille de la pile.
 */
int pile_taille(Pile P);

/**
 * \fn void pile_affichage(Pile P)
 * \brief Fonction qu.i affiche la pile
 *
 * \param P la pile que l'on souhaite afficher.
 * \return ??
 */
void pile_affichage(Pile P);


#endif
