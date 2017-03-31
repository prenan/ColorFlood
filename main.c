#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include "SDL.h"
#include "n_tree.h"
/*#include "solveur.h"*/

int main()
{
	int size = choose_size();
	int nbr_coup = 0, nbr_coups_max=30;
	char nbr_coup_texte[30];
	char* chemin = malloc(sizeof(char));
	TTF_Font *police1 = NULL, *police2 = NULL;
	int size_window =500-500%size;

	TTF_Init();

	police1 = TTF_OpenFont("liberation.ttf", 20);
	police2 = TTF_OpenFont("liberation.ttf", 50);

	grille plateau = random_grille(size);

	NTree root=newNTree(plateau[0][0]);
	solution(plateau, root, size);
	tree_delete(root);

	grille sol_plateau=initialize(size);
	sol_plateau = copie(plateau,size);

	SDL_Surface *ecran = initialize_screen(size_window);

	sprintf(nbr_coup_texte, "Nombre de coups : %d/%d", nbr_coup, nbr_coups_max);

	initialize_text(ecran, nbr_coup_texte, police1);
	
	display_SDL(ecran, plateau, size,size_window);

	nbr_coup = loop_game(ecran, plateau, size, nbr_coups_max, nbr_coup_texte, police1, size_window);
	end_game(ecran, plateau, size, nbr_coup, nbr_coups_max, police2);
	
	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
	TTF_Quit();
	
	SDL_Quit();
	free(chemin);
	free_space(sol_plateau, size);
	free_space(plateau, size);

	return 0;
}