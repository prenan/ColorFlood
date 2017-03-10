#include <math.h>
#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"

#include <SDL/SDL.h>

#define size_window 500

struct RGB
{
	int r;
	int g;
	int b;
};

typedef struct RGB RGB;

RGB J = {255,255,0};
RGB R = {255,0,0};
RGB G = {192,192,192};
RGB V = {0,255,0};
RGB B = {0,0,255};
RGB M = {128,0,128};
RGB init_screen = {255,255,255};

/* px, py coordonnées haut, gauche du pixel */
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
{
	SDL_Rect rect;
	rect.x=px;
	rect.y=py;
	rect.h=rect.w=size;
	SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);
}

/*SDL_FillRect(pointeur ecran, NULL pour tout remplir, couleur)
permet de remplir l'écran entier d'une couleur*/
void fillScreen(SDL_Surface *ecran, RGB couleur)
{
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);	/*MàJ de l'écran*/
}

void pause1()
{
	int continuer = 1;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
			continuer = 0;
		}
	}
}

void display_SDL(grille plateau, int size, SDL_Surface *ecran)
{
	int i, j;
	char couleur;
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			couleur = plateau[i][j].color;
			switch (couleur)
			{
				case 'B':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, B);
				break;

				case 'V':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, V);
				break;

				case 'R':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, R);
				break;

				case 'J':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, J);
				break;

				case 'M':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, M);
				break;

				case 'G':
				drawRectangle(ecran, i*size_window/size, j*size_window/size, size_window/size, G);
				break;
			}
		}
	}
}

int main()
{
	int size = 5, i;
	int nbr_coup=0;
	int nbr_coups_max = floor(2.1*size-1 + 0.5);

	grille plateau = random_grille(size);
	char couleur = plateau[0][0].color;
	modif_color(couleur, plateau, size);

	int continuer = 1;
	SDL_Surface *ecran = NULL;
	SDL_Event event;
	const SDL_VideoInfo* info = NULL;

	/* chargement de la SDL et vérif erreur */
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

	
	/* fenêtre de taille size_window*size_window avec 8 bits couleur*/
	ecran = SDL_SetVideoMode(size_window, size_window, 8, SDL_HWSURFACE);
	/* nom de la fenêtre */
	SDL_WM_SetCaption("Jeu - Color Flood", NULL);
	/* écran tout blanc */
	fillScreen(ecran, init_screen);
	display_SDL(plateau, size, ecran);
	while(if_flood(plateau, size) != 1 && nbr_coup<nbr_coups_max && continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_b:
				if (plateau[0][0].color != 'B')
				{
					modif_color('B', plateau, size);
					nbr_coup++;
					display_SDL(plateau, size, ecran);
				}
				break;

				case SDLK_v:
				if (plateau[0][0].color != 'V')
				{
					modif_color('V', plateau, size);
					nbr_coup++;
					display_SDL(plateau, size, ecran);
				}
				break;

				case SDLK_r:
				if (plateau[0][0].color != 'R')
				{
					modif_color('R', plateau, size);
					nbr_coup++;
					display_SDL(plateau, size, ecran);
				}
				break;

				case SDLK_j:
				if (plateau[0][0].color != 'J')
				{
					modif_color('J', plateau, size);
					nbr_coup++;
					display_SDL(plateau, size, ecran);
				}
				break;

				case SDLK_m:
				if (plateau[0][0].color != 'M')
				{
					modif_color('M', plateau, size);
					nbr_coup++;
					display_SDL(plateau, size, ecran);
				}
				break;

				case SDLK_g:
				if (plateau[0][0].color != 'G')
				{
					modif_color('G', plateau, size);
					nbr_coup++;
					display_SDL(plateau, size, ecran);
				}
				break;

				case SDLK_ESCAPE:
				continuer = 0;
				break;

				default:
				break;
			}
			
		}
	}

	SDL_Quit();

	for (i=0;i<size;i++)
	{
		free(plateau[i]);
		plateau[i]=NULL;
	}
	free(plateau);
	plateau = NULL;

	return 0;
}
/*
	int continuer = 1;
	SDL_Event event;
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
			continuer = 0;
			break;
			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_b:
				drawRectangle(ecran, 250, 250, 2, 255, 255, 255);
				break;
				case SDLK_v:
				case SDLK_r:
				case SDLK_j:
				case SDLK_m:
				case SDLK_g:
				case SDLK_ESCAPE:
				continuer=0;
				break;
			}
		}
	}
*/