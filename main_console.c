#include <math.h>
#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"

int main()
{
	int i, size, nbr_coup=0;
	size = choose_size();

	int nbr_coups_max = floor(2.1*size-1 + 0.5);
	grille M = random_grille(size);
	char ancienne_couleur = M[0][0], buffer[2], couleur;

	display(M, size);
	printf("%d/%d coups\n",nbr_coup,nbr_coups_max);
	export_file(M, size);
	
	while(if_flood(M, size) != 1 && nbr_coup<nbr_coups_max)
	{
		printf("Entrer B, V, R, J, M ou G pour les couleurs. Q pour quitter : ");
		scanf("%1s", buffer);
		couleur = buffer[0];
		if(couleur == 'Q')
		{	
			printf("Vous avez quitté la partie !\n");
			break;
		}
		if (couleur=='B' || couleur=='V'|| couleur=='R' || couleur=='J' || couleur=='M' || couleur=='G')
		{
			modif_color(0,0, couleur, ancienne_couleur, M, size);
			nbr_coup++;
		}
		else
		{
			printf("\nLa couleur choisie n'est pas possible.\n");
		}
		display(M, size);
		printf("%d/%d coups\n", nbr_coup, nbr_coups_max);
	}
	if(if_flood(M,size)==1 && nbr_coup<=nbr_coups_max)
		printf("Vous avez gagné !\n");
	if(if_flood(M, size) == 0 && nbr_coup >= nbr_coups_max)
		printf("Vous avez perdu !\n");
	for (i=0;i<size;i++)
	{
		free(M[i]);
		M[i]=NULL;
	}
	free(M);
	M = NULL;
	
	return 0;
}