#include <math.h>
#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"

int main()
{
	int i, size;
	int test_color=0;
	int nbr_coup=0;
	printf("Entrer la taille du jeu (entre 4 et 24)\n");
	scanf("%d",&size);
	while(size<4 || size >24)
	{
		printf("La taille doit être comprise entre 4 et 24.\n");
		scanf("%d",&size);
	}
	int nbr_coups_max = floor(2.1*size-1 + 0.5);
	grille M = random_grille(size);
	char couleur = M[0][0].color;
	char buffer[2];

	display(M, size);
	printf("%d/%d coups\n",nbr_coup,nbr_coups_max);
	export_file(M, size);
	modif_color(couleur, M, size);
	
	while(if_flood(M, size) != 1 && nbr_coup<nbr_coups_max)
	{
		printf("Entrer B, V, R, J, M ou G  pour les couleurs\nQ pour quitter: ");
		scanf("%1s", buffer);
		couleur = buffer[0];
		if(couleur == 'Q')
			break;
		if ((couleur!=M[0][0].color) && (couleur=='B'||couleur=='V'||couleur=='R'||couleur=='J'||couleur=='M'||couleur=='G'))
			{
				test_color=1;
			}
		switch (test_color)
		{
			case (1):
			{
				modif_color(couleur, M, size);
				nbr_coup++;
				break;
			}
			default:
			{
				printf("La couleur choisie n'est pas possible \n");
			}

		}
		display(M, size);
		printf("%d/%d coups\n",nbr_coup,nbr_coups_max);
		scanf("%c", &couleur);
		printf("\n");
		test_color=0;
	}
	if (couleur=='Q')
		printf("Vous avez quitté la partie !\n");
	if(if_flood(M,size)==1 && nbr_coup<=nbr_coups_max)
		printf("Vous avez gagné !\n");
	if(nbr_coup>nbr_coups_max)
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