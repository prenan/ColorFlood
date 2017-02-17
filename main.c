#include <stdio.h>
#include <stdlib.h>

#include "fichier.h"
#include "grille.h"
#include "pile.h"

int main()
{
	char couleur;
	grille M = init_file(size_file("fichier_grille.txt"), "fichier_grille.txt");
	display(M,15);

	while(if_flood(M,15)!=1)
	{
		scanf("%c",&couleur);
		modif_color(couleur,M,15);
		display(M,15);
		scanf("%c",&couleur);
		printf("\n");

	}

	printf("Vous avez gagné\n");

	return 0;
}
