#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SOLVEUR_H
#define SOLVEUR_H

char* solution(grille plateau, int size, int *nbr_coups);

char* solution_opti(grille plateau, int size,int *nbr_coups);

int compteur_appartenance(grille plateau, int size);

char* solveur(grille plateau, int size, int* nbr_coups,char* chemin);

int testeur_chemins(char* chemin, grille plateau, int size);

char* copie_texte(char* chemin, char couleur);

#endif