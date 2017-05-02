#include "fichier.h"
#include "grille.h"
#include "SDL.h"
#include "solveur.h"

int main()
{
	int size = 0, difficulte = 0, nbr_coup = 0, nbr_coups_max = 0, bouton, out;
	int size_window = 0;	/*taille de la fenetre dépendra de size*/
	bool border_flag;
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

	SDL_WM_SetIcon(SDL_LoadBMP("img/colorflood.bmp"), NULL);	/*icône de la fenêtre*/
	
	do {
		ecran = menu(police1, police2, police3, &size, &difficulte, &nbr_coups_max, &border_flag);

		if (size != 0)
		{
			grille plateau = random_grille(size);
			grille plateau_sol = copie(plateau, size);

			solution_rapide(plateau_sol, size, &nbr_coups_max);	/*utile pour le niveau de difficulté*/
			
			nbr_coups_max += 5/difficulte; /*niveau de difficulté*/
			do {
				plateau_copie = copie(plateau, size);
				size_window = 500;
				ecran = initialize_screen(size_window);

				sprintf(nbr_coup_texte, "%d/%d", nbr_coup, nbr_coups_max);

				initialize_text(ecran, nbr_coup_texte, police1);
				
				display_SDL(ecran, plateau, size, size_window, border_flag);

				nbr_coup = loop_game(ecran, plateau, size, nbr_coups_max, nbr_coup_texte, police1, size_window, border_flag, &bouton, &out);

				end_game(ecran, plateau, size, nbr_coup, nbr_coups_max, police2);

				plateau = plateau_copie;
			} while (bouton == 2 && out != 1);

			free_space(plateau, size);
			free_space(plateau_sol, size);
			/*free_space(plateau_copie, size); FAIT PLANTER LE MENU*/
		}
	} while (bouton == 1 && size != 0);

	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
	TTF_CloseFont(police3);
	TTF_Quit();

	SDL_Quit();

	return 0;
}