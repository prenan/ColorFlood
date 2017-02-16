#include <stdio.h>
#include <stdlib.h>

#include "fichier.h"
#include "grille.h"
#include "pile.h"

int main()
{
	Pile tache=NULL;
	
	grille M = init_file(size_file("fichier_grille.txt"), "fichier_grille.txt");
	display(M, 15);

	printf("\ndébut d'identification\n");

	tache = identifier_tache(M, 'R', 15);

	printf("fin d'identification\n \naffichage de pile finale \n");

	pile_affichage(tache);

	printf("\ntaille de la tache %d\n", pile_taille(tache));

	/*
	printf("%d\n",if_flood(M, 15));       
	M = change_color(0, 4, 'B', M);
	display(M, 15);
	printf("%d\n",if_flood(M, 15));       
	*/
	return 0;
}
