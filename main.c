#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"

int main()
{
	int size = choose_size();
	int nbr_coup = 0, nbr_coups_max = floor(2.1*size-1 + 0.5);
	char nbr_coup_texte[30];

	SDL_Surface *textes[4];
	TTF_Font *police1 = NULL, *police2 = NULL;

	TTF_Init();

	police1 = TTF_OpenFont("liberation.ttf", 20);
	police2 = TTF_OpenFont("liberation.ttf", 50);

	grille plateau = random_grille(size);
	char couleur = plateau[0][0].color;
	modif_color(couleur, plateau, size);

	SDL_Surface *ecran = initialize_screen();
	
	sprintf(nbr_coup_texte, "Nombre de coups : %d/%d", nbr_coup, nbr_coups_max);
	/*initialize_text(ecran, nbr_coup_texte, police1, &textes);*/

while(1){
	display_SDL(plateau, size, ecran);

}

	loop_game(ecran, plateau, size, nbr_coup, nbr_coups_max, nbr_coup_texte, police1, textes[2]);

	end_game(ecran, plateau, size, nbr_coup, nbr_coups_max, police2, textes);
	
	TTF_CloseFont(police1);
	TTF_CloseFont(police2);

	TTF_Quit();

	SDL_Quit();

	return 0;
}