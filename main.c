#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"

int main()
{
	int i, size = 4;
	int test_color=0;
	grille M = random_grille(size);
	char couleur = M[0][0].color;
	char buffer[2];

	display(M, size);

	export_file(M, size);
	modif_color(couleur, M, size);
	
	while(if_flood(M, size) != 1)
	{
		printf("Entrer B, V, R, J, M ou G : ");
		scanf("%1s", buffer);
		couleur = buffer[0];
		if ((couleur!=M[0][0].color) && (couleur=='B'||couleur=='V'||couleur=='R'||couleur=='J'||couleur=='M'||couleur=='G'))
			{
				test_color=1;
			}
		switch (test_color)
		{
			case (1):
			{
				modif_color(couleur, M, size);
				break;
			}
			default:
			{
				printf("La couleur choisie n'est pas possible \n");
			}

		}
		display(M, size);
		scanf("%c", &couleur);
		printf("\n");
		test_color=0;
	}
	for (i=0;i<size;i++)
	{
		free(M[i]);
		M[i]=NULL;
	}
	free(M);
	M = NULL;

	printf("Vous avez gagné !\n");

	return 0;
}