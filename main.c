#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include "solveur.h"

int main()
{
	int size = 0; /* taille du jeu sera indiquée au menu par le joueur */
	int size_window = 0; /* taille de la fenetre dépendra de size */
	int nbr_coup = 0, nbr_coups_max;
	char nbr_coup_texte[50];
	SDL_Surface *ecran = NULL;
	TTF_Font *police1 = NULL, *police2 = NULL;

	/* initialisation da la SDL */
	const SDL_VideoInfo *info = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		SDL_Quit();
	}

	info = SDL_GetVideoInfo();
	if(!info)
	{
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		SDL_Quit();
	}
	/*fin d'initialisation de la SDL */ 

	TTF_Init();

	police1 = TTF_OpenFont("liberation.ttf", 20);
	police2 = TTF_OpenFont("liberation.ttf", 50);

	ecran = menu(police1, police2, &size);
	if (size != 0)
	{
		grille plateau = random_grille(size);

		
		nbr_coups_max = 30; /*niveau de difficulté*/

		size_window =500-500%size;
		ecran = initialize_screen(size_window);

		sprintf(nbr_coup_texte, "Nombre de coups : %d/%d. Solveur : %d coups", nbr_coup, nbr_coups_max, 31);

		initialize_text(ecran, nbr_coup_texte, police1);
		
		display_SDL(ecran, plateau, size,size_window);

		nbr_coup = loop_game(ecran, plateau, size, nbr_coups_max, nbr_coup_texte, police1, size_window);
		end_game(ecran, plateau, size, nbr_coup, nbr_coups_max, police2);

		free_space(plateau, size);
	}

	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
	TTF_Quit();
		
	SDL_Quit();

	return 0;
}