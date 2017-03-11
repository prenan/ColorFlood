#include "SDL.h"


void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
{
	SDL_Rect rect;
	rect.x=px;
	rect.y=py;
	rect.h=rect.w=size;
	SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);
}

void fillScreen(SDL_Surface *ecran, RGB couleur)
{
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);	/*MàJ de l'écran*/
}

SDL_Surface *initialize_screen()
{
	SDL_Surface *ecran = NULL;
	const SDL_VideoInfo *info = NULL;
	RGB init_screen = {255, 255, 255};	/* blanc */

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

	ecran = SDL_SetVideoMode(size_window, size_window+200, 8, SDL_HWSURFACE);
	/* nom de la fenêtre */
	SDL_WM_SetCaption("Color Flood (THOR)", NULL);
	/* écran tout blanc */
	fillScreen(ecran, init_screen);

	return ecran;
}

void initialize_text(SDL_Surface *ecran, char *nbr_coup_texte, TTF_Font *police)
{
	SDL_Rect position1, position2, position3;
	SDL_Color texteNoir = {0, 0, 0, 42}, fondBlanc = {255, 255, 255, 42};	/* 4ème paramètre inutile */
	SDL_Surface *texte1, *texte2, *texte3;
	texte1 = TTF_RenderText_Shaded(police, "Pour jouer : taper 'B', 'V', 'R', 'J', 'M' ou 'G'.", texteNoir, fondBlanc);
	texte2 = TTF_RenderText_Shaded(police, "Pour quitter : taper 'echap'.", texteNoir, fondBlanc);
	texte3 = TTF_RenderText_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);
	position1.x = 5;
	position1.y = 610;
	position2.x = 5;
	position2.y = 660;
	position3.x = 5;
	position3.y = 510;
	SDL_BlitSurface(texte1, NULL, ecran, &position1);
	SDL_BlitSurface(texte2, NULL, ecran, &position2);
	SDL_BlitSurface(texte3, NULL, ecran, &position3);
}

void display_SDL(SDL_Surface *ecran, grille plateau, int size)
{
	RGB J = {255, 215, 0};
	RGB R = {219, 23, 2};
	RGB G = {127, 127, 127};
	RGB V = {1, 215, 88};
	RGB B = {0, 127, 255};
	RGB M = {128, 0, 128};
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

int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police)
{
	int continuer = 1, nbr_coup = 0;
	SDL_Surface *texte;
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42}, fondBlanc = {255, 255, 255, 42};
	SDL_Rect position;
	position.x = 5;
	position.y = 510;

	while(if_flood(plateau, size) != 1 && nbr_coup < nbr_coups_max && continuer)
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
				}
				break;

				case SDLK_v:
				if (plateau[0][0].color != 'V')
				{
					modif_color('V', plateau, size);
					nbr_coup++;
				}
				break;

				case SDLK_r:
				if (plateau[0][0].color != 'R')
				{
					modif_color('R', plateau, size);
					nbr_coup++;
				}
				break;

				case SDLK_j:
				if (plateau[0][0].color != 'J')
				{
					modif_color('J', plateau, size);
					nbr_coup++;
				}
				break;

				case SDLK_m:
				if (plateau[0][0].color != 'M')
				{
					modif_color('M', plateau, size);
					nbr_coup++;
				}
				break;

				case SDLK_g:
				if (plateau[0][0].color != 'G')
				{
					modif_color('G', plateau, size);
					nbr_coup++;
				}
				break;

				case SDLK_ESCAPE:
				continuer = 0;
				break;

				default:
				break;
			}
			sprintf(nbr_coup_texte, "Nombre de coups : %d/%d", nbr_coup, nbr_coups_max);
			texte = TTF_RenderText_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);
			SDL_BlitSurface(texte, NULL, ecran, &position);
			display_SDL(ecran, plateau, size);
		}
	}
	return nbr_coup;
}

void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police)
{
	SDL_Color texteNoir = {0, 0, 0, 42};

	SDL_Surface *texte = NULL;
	SDL_Rect position;

	if (nbr_coup >= nbr_coups_max && if_flood(plateau, size) == 0)
	{
		texte = TTF_RenderText_Blended(police, "GAME OVER", texteNoir);
		position.x = 110;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(4);
	}
	if (if_flood(plateau, size) == 1)
	{
		texte = TTF_RenderText_Blended(police, "WIN", texteNoir);
		position.x = 190;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(4);
	}
}

void free_surface(SDL_Surface **textes)
{
	SDL_FreeSurface(textes[0]);
	SDL_FreeSurface(textes[1]);
	SDL_FreeSurface(textes[2]);
	SDL_FreeSurface(textes[3]);
}