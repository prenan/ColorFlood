#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SOLVEUR_H
#define SOLVEUR_H

int solution(grille plateau, int size);

int solution_opti(grille plateau, int size);

int compteur_appartenance(grille plateau, int size);

#endif