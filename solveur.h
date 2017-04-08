/**
 * \file solveur.h
 * \brief Fonctions pour les différents solveurs
 * \author THOR
 * \date avril 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grille.h"

#ifndef SOLVEUR_H
#define SOLVEUR_H


/**
 * \fn SDL_Surface *initialize_screen(int size_window)
 * \brief Initialisation de la fenêtre.
 * \param size_window Taille de l'écran de jeu.
 * \return La surface, ie. l'écran de la fenêtre.
 */
/*char* solution_opti(grille plateau, int size, int *nbr_coups);*/

/**
 * \fn int testeur_chemins(grille plateau, int size, char* chemin)
 * \brief Test si le chemin permet d'inonder le plateau.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param chemin Chemin à tester.
 * \return 1 si le plateau est entièrement inondé d'une couleur en effectuant le chemin,
 	0 sinon.
 */
bool testeur_chemins(grille plateau, int size, char* chemin);

/**
 * \fn char* concatener(char* chemin, char* couleur)
 * \brief Concaténer le chemin et une couleur.
 * \param chemin Chemin.
 * \param couleur Couleur.
 * \return Une chaîne de caractères (le chemin puis la couleur bout à bout).
 */
char* concatener(char* chemin, char* couleur);

/**
 * \fn char* solveur_brut(grille plateau, int size, int *nbr_coups)
 * \brief Solveur : détermine le chemin le plus court pour terminer la partie
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param nbr_coups_min Le nombre de coups du chemin le plus court trouvé.
 * \return Une chaîne de caractères (le chemin puis la couleur bout à bout).
 */
char* solveur_brut(grille plateau, int size, int *nbr_coups_min);

/**
 * \fn void free_chemins(char*** chemins, int i, int j, int k, int l)
 * \brief Libération de la mémoire des chemins.
 *
 * \param chemins Chemins à libérer.
 * \param i la taille maximale de nos chemins (en effectuant des tests on a remarqué qu'on avaait jamais plus de 60 coups).
 * \param j le nombre de chemins différent lorsqu'on est à l'étage i.
 * \param k l'étage où l'on a trouvé la solution. 
 * \param l la position de cette solution au sein de l'étage.
 */
void free_chemins(char*** chemins, int i, int j, int k, int l);


#endif