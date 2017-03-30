#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "grille.h"

typedef struct NTree Nnode,*NTree;

int NTreeVide(NTree a);

NTree nouvelNTree(char c);

/**
 ** @brief create a new node with initial color c
 **/

NTree insert(NTree a,char c);

void affNTreeRec(NTree a, int num);

void node_delete(NTree n);

/**
 **  detect if n has children
 **/

bool node_isinner(NTree n);

/**
 ** detect if @a n is a leaf
 **/

bool node_isleaf(NTree n);


void tree_delete(NTree n);