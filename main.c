#include "fichier.h"
#include "grille.h"
#include "pile.h"

int main()
{
	grille M = init_file(size_file("fichier_grille.txt"), "fichier_grille.txt");
	char couleur=M[0][0].color;

	display(M, size_file("fichier_grille.txt"));

	export_file(M, size_file("fichier_grille.txt"));
	modif_color(couleur,M,size_file("fichier_grille.txt"));
	while(if_flood(M,size_file("fichier_grille.txt"))!=1)
	{
		scanf("%c",&couleur);
		modif_color(couleur,M,size_file("fichier_grille.txt"));
		display(M,size_file("fichier_grille.txt"));
		scanf("%c",&couleur);
		printf("\n");

	}

	printf("Vous avez gagné\n");

	return 0;
}
