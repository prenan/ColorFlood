#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "grille.h"

typedef struct t_narbre NNoeud,*NArbre;

int narbreVide(NArbre a);

NArbre nouvelNArbre(char c);

/**
 ** @brief create a new node with initial color c
 **/

NArbre insert(NArbre a,NArbre fils);

void affNArbreRec(NArbre a, int num);

void node_delete(NArbre n);

/**
 **  detect if n has children
 **/

bool node_isinner(NArbre n);

/**
 ** detect if @a n is a leaf
 **/

bool node_isleaf(NArbre n);


void tree_delete(NArbre n);