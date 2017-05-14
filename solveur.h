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
#include <sys/time.h>
#include "grille.h"

#ifndef SOLVEUR_H
#define SOLVEUR_H


/**
 * \fn char* concatener(char* chemin, char* couleur)
 * \brief Concaténer le chemin et une couleur
 *
 * \param chemin Chemin (séquence de lettres)
 * \param couleur Couleur à rajouter à la fin du chemin
 * \return Une chaîne de caractères (le chemin puis la couleur bout à bout)
 */
char* concatener(char* chemin, char* couleur);

/**
 * \fn bool testeur_chemins(grille plateau, int size, char* chemin)
 * \brief Test si le chemin permet d'inonder le plateau
 *
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param chemin Chemin à tester
 * \return 1 si le plateau est entièrement inondé d'une couleur en effectuant le chemin,
 	0 sinon
 */
bool testeur_chemins(grille plateau, int size, char* chemin);

/**
 * \fn void comparateur_avancement(grille plateau, int size, int* valeur)
 * \brief Remplit un tableau de valeurs avec le nombre de cases connexes pour chaque couleur
 *
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param valeur Tableau contenant le nombre de cases connexes pour chaque couleur
 */
void comparateur_avancement(grille plateau, int size, int* valeur);

void comparateur_avancement2(grille plateau, int size, int* valeur, int ancien_nb_couleur);

/**
 * \fn int minimum(int* tableau)
 * \brief Trouve la valeur minimale du tableau
 *
 * \param tableau Tableau dont on cherche le minimum
 * \return La valeur minimale du tableau
 */
int minimum(int* tableau);

/**
 * \fn char* solution_rapide(grille plateau, int size, int *nbr_coups)
 * \brief Solveur : détermine une solution rapidement du jeu (relativement optimisée)
 *
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param nbr_coups Pointeur pour stocker le nombre de coups du chemin le plus court trouvé
 * \return Un chemin (chaîne de caradctères) assez court pour terminer la partie
 */
char* solution_rapide(grille plateau, int size, int *nbr_coups);

/**
 * \fn char* solveur_brut(grille plateau, int size, int *nbr_coups)
 * \brief Solveur : détermine un chemin le plus court pour terminer la partie (non-optimisé)
 *
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param nbr_coups_min Nombre de coups du chemin le plus court trouvé
 * \return Un chemin le plus court pour terminer la partie
 */
char* solveur_brut(grille plateau, int size, int *nbr_coups_min);

/**
 * \fn char* solveur_perf(grille plateau, int size, int *nbr_coups_min)
 * \brief Solveur : détermine un chemin le plus court pour terminer la partie (optimisé)
 *
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param nbr_coups_min Pointeur pour stocker le nombre de coups du chemin le plus court trouvé
 * \return Une chaîne de caractères contenant un chemin minimal.
 */
char* solveur_perf(grille plateau, int size, int *nbr_coups_min);

/**
 * \fn void free_c(char** chemins, int k)
 * \brief Libération de la mémoire des chemins
 *
 * \param chemins Chemins à libérer
 * \param k Nombre d'éléments sur la ligne
 */
void free_c(char** chemins, int k);

/**
 * \fn void free_chemins(char*** chemins, int i, int j, int k, int l)
 * \brief Libération de la mémoire des chemins
 *
 * \param chemins Chemins à libérer
 * \param i Taille maximale de nos chemins (< 60 coups après plusieurs tests)
 * \param j Nombre de chemins différents lorsqu'on est à l'étage i
 * \param k Étage où l'on a trouvé la solution 
 * \param l Position de cette solution au sein de l'étage
 */
void free_chemins(char*** chemins, int i, int j, int k, int l);


#endif