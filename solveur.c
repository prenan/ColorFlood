#include "solveur.h"

int solution(SDL_Surface *ecran, grille plateau, int size)
{
	int nbr_coups = 0, i;
	char* couleurs = "BVRJMG";
	while(if_flood(plateau, size)==0)
	{
		if (plateau[0][0].color != couleurs[i])	
		{
			modif_color (couleurs[i], plateau, size);
			i++;
		}
		else
		{
			i++;
			modif_color (couleurs[i], plateau, size);
		}
		display_SDL(ecran, plateau, size);
		nbr_coups ++;
		i%=6;
	}
	return nbr_coups;
}