#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include "solveur.h"

int main()
{
	int size = choose_size();
	int nbr_coup = 0, nbr_coups_max;
	char nbr_coup_texte[30];
	TTF_Font *police1 = NULL, *police2 = NULL;
	int size_window =500-500%size;

	TTF_Init();

	police1 = TTF_OpenFont("liberation.ttf", 20);
	police2 = TTF_OpenFont("liberation.ttf", 50);
	grille plateau = random_grille(size);

	char* chemin = solveur_brut(plateau, size, &nbr_coups_max);
	printf("Solveur : %s\n", chemin);

	SDL_Surface *ecran = initialize_screen(size_window);

	sprintf(nbr_coup_texte, "Nombre de coups : %d/%d. Solveur : %d coups", nbr_coup, nbr_coups_max, nbr_coups_max);

	initialize_text(ecran, nbr_coup_texte, police1);
	
	display_SDL(ecran, plateau, size,size_window);

	nbr_coup = loop_game(ecran, plateau, size, nbr_coups_max, nbr_coup_texte, police1, size_window);
	end_game(ecran, plateau, size, nbr_coup, nbr_coups_max, police2);
	
	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
	TTF_Quit();
	
	SDL_Quit();
	free(chemin);
	free_space(plateau, size);

	return 0;
}