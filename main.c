#include "fichier.h"
#include "grille.h"
#include "SDL.h"
#include "solveur.h"

int main()
{
	int size_window = 500, size = 0, difficulte = 0, nbr_coups = 0, nbr_coups_max = 0, bouton, out;
	char nbr_coups_texte[50];

	SDL_Surface *ecran = NULL;
	TTF_Font *police_petite = NULL, *police_moyenne = NULL, *police_grande = NULL;

	/*initialisation da la SDL*/
	const SDL_VideoInfo *info = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		SDL_Quit();
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) // initialisation de l'API Mixer
		printf("%s", Mix_GetError());

	info = SDL_GetVideoInfo();
	if(!info)
	{
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		SDL_Quit();
	}
	/*fin d'initialisation de la SDL*/ 

	TTF_Init();

	police_petite = TTF_OpenFont("orkney.ttf", 20);
	police_moyenne = TTF_OpenFont("orkney.ttf", 50);
	police_grande = TTF_OpenFont("orkney.ttf", 70);

	SDL_WM_SetIcon(SDL_LoadBMP("img/colorflood.bmp"), NULL);	// icône de la fenêtre
	
	do {
		ecran = menu(police_moyenne, police_grande, &size, &difficulte, &nbr_coups_max);

		if (size != 0)
		{
			grille plateau = random_grille(size), plateau_sol = copie(plateau, size), plateau_copie;
			solution_rapide(plateau_sol, size, &nbr_coups_max);	// utile pour le niveau de difficulté
			nbr_coups_max += 5/difficulte; // niveau de difficulté
			
			do {
				plateau_copie = copie(plateau, size);
				
				ecran = initialize_screen(size_window);
				initialize_text(ecran, police_petite, nbr_coups_texte, size, difficulte);
				display_plateau(ecran, plateau, size, size_window, size_window*0.5-10, 20);

				nbr_coups = loop_game(ecran, plateau, size, nbr_coups_max, nbr_coups_texte, police_petite, police_moyenne, size_window, &bouton, &out);

				plateau = plateau_copie;
			} while (bouton == 2 && out != 1);

			free_space(plateau, size);
			free_space(plateau_sol, size);
			/*free_space(plateau_copie, size); FAIT PLANTER LE MENU*/
		}
	} while (bouton == 1 && size != 0 && out != 1);

	TTF_CloseFont(police_petite);
	TTF_CloseFont(police_moyenne);
	TTF_CloseFont(police_grande);
	TTF_Quit();

	SDL_Quit();

	return 0;
}