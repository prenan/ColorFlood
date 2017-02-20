/**
 * \file grille.h
 * \brief Fonctions sur les grilles et définition d'une structure
 * \author THOR
 * \date février 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "pile.h"

#ifndef GRILLE_H
#define GRILLE_H

/**
 * \struct element
 * \brief Structure d'une case du plateau
 *
 * Pour une case, on a son appartenance à la tâche ou non (int)
 * ainsi que sa couleur (char).
 */
struct element
{
	int appartenance;
	char color;
};

typedef struct element element;

typedef element ** grille;


/**
 * \fn grille initialize(int size)
 * \brief Fonction d'initialisation d'une grille.
 *
 * \param size Taille du jeu (grille à initialiser size*size), doit être compris entre ??.
 * \return Grille de taille size*size.
 */
grille initialize(int size);

/**
 * \fn void display(grille plateau, int size)
 * \brief Fonction d'affichage d'une grille.
 *
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \return Affichage du plateau.
 */
void display(grille plateau, int size);
grille random(int size);
void free_space(grille plateau, int size);
grille change_color(int i, int j, char c, grille plateau);  /* Change color with index and choosed color--HAO */
bool if_flood(grille plateau, int size);  /* To see whether color flood */

int test_neighbour(grille plateau, coordonnees coord, int size, char couleur_choisie);
void modif_color (char couleur_choisie, grille plateau, int size);

Pile Deep(char couleur_choisie, grille plateau, int size,coordonnees position_pere,Pile P);


#endif
