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
 * \fn bool testeur_chemins(grille plateau, int size, char* chemin)
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

/**
 * \fn void comparateur_avancement(grille plateau, int size, int* valeur)
 * \brief Remplit un tableau de valeur avec le nombre de cases connexes pour chaque couleur.
 *
 * \param plateau le plateau de jeu.
 * \param size la taille du plateau.
 * \param valeur le tableau contenant le nombre de cases connexes pour chaque couleur.
 */
void comparateur_avancement(grille plateau, int size,int* valeur);

/**
 * \fn void free_c(char** chemins, int k)
 * \brief Libération de la mémoire des chemins.
 *
 * \param chemins Chemins à libérer.
 * \param k nombre d'éléments sur la ligne. 
 */
void free_c(char** chemins,int k);

/**
 * \fn int minimum(int* valeur)
 * \brief Trouve la valeur minimale du tableau.
 *
 * \param valeur le tableau dont on cherche le minimum. 
 * \return La valeur minimale du tableau.
 */
int minimum(int* valeur);

/**
 * \fn char* solveur_perf(grille plateau, int size, int *nbr_coups)
 * \brief Solveur : détermine le chemin le plus court pour terminer la partie de manière plus optimale.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param nbr_coups_min Le nombre de coups du chemin le plus court trouvé.
 * \return Une chaîne de caractères contenant un chemin minimal.
 */
char* solveur_perf(grille plateau, int size, int *nbr_coups_min);

/**
 * \fn char* solution_rapide(grille plateau, int size, int *nbr_coups)
 * \brief Solveur : détermine une solution rapidement du jeu (relativement optimisée).
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param nbr_coups Pointeur pour enregistrer le nombre de coups du chemin le plus court trouvé.
 * \return Une chaîne de caractères contenant une solution proche de la minimale.
 */
char* solution_rapide(grille plateau, int size, int *nbr_coups);


#endif