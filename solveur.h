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
char* solution_opti(grille plateau, int size, int *nbr_coups);

int testeur_chemins(grille plateau, int size, char* chemin);

char* copie_texte(char* chemin, char* couleur);

char* solveur_brut(grille plateau, int size, int *nbr_coups);

void free_chemins(char*** chemins, int i, int j, int k, int l);


#endif