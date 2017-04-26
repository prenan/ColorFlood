#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include "solveur.h"

int main()
{
	int size = 0, difficulte = 0, nbr_coup = 0, nbr_coups_max = 0;
	int size_window = 0;	/*taille de la fenetre dépendra de size*/
	char nbr_coup_texte[50];

	SDL_Surface *ecran = NULL;
	TTF_Font *police1 = NULL, *police2 = NULL, *police3 = NULL;

	/*initialisation da la SDL*/
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
	/*fin d'initialisation de la SDL*/ 

	TTF_Init();

	police1 = TTF_OpenFont("orkney.ttf", 20);
	police2 = TTF_OpenFont("orkney.ttf", 50);
	police3 = TTF_OpenFont("orkney.ttf", 70);

	ecran = menu(police3, police2, &size, &difficulte, &nbr_coups_max);

	if (size != 0)
	{
		grille plateau = random_grille(size);

		grille plateau_sol = copie(plateau,size);

		solution_rapide(plateau_sol, size, &nbr_coups_max);	/*utile pour le niveau de difficulté*/
		
		nbr_coups_max += 5/difficulte; /*niveau de difficulté*/

		size_window = 500-500%size;
		ecran = initialize_screen(size_window);

		sprintf(nbr_coup_texte, "Nombre de coups : %d/%d", nbr_coup, nbr_coups_max);

		initialize_text(ecran, nbr_coup_texte, police1);
		
		display_SDL(ecran, plateau, size,size_window);

		nbr_coup = loop_game(ecran, plateau, size, nbr_coups_max, nbr_coup_texte, police1, size_window);
		end_game(ecran, plateau, size, nbr_coup, nbr_coups_max, police2);

		free_space(plateau, size);
		free_space(plateau_sol, size);
	}

	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
	TTF_CloseFont(police3);
	TTF_Quit();

	SDL_Quit();

	return 0;
}