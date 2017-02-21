#include "fichier.h"
#include "grille.h"
#include "pile.h"

int main()
{
	int size = size_file("fichier_grille.txt");
	grille M = init_file(size, "fichier_grille.txt");
	char couleur = M[0][0].color;

	display(M, size);

	export_file(M, size);
	modif_color(couleur, M, size);
	
	while(if_flood(M, size) != 1)
	{
		scanf("%c", &couleur);
		modif_color(couleur, M, size);
		display(M, size);
		scanf("%c", &couleur);
		printf("\n");

	}
	printf("Vous avez gagné\n");

	return 0;
}
