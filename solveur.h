#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SOLVEUR_H
#define SOLVEUR_H

int solution(SDL_Surface *ecran, grille plateau, int size);

int solution_opti(SDL_Surface *ecran, grille plateau, int size);

int compteur_appartenance(grille plateau, int size);

grille copie(grille plateau, int size);


#endif