#include "SDL.h"

	RGB B = {0, 127, 255};
	RGB V = {1, 215, 88};
	RGB R = {219, 23, 2};
	RGB J = {255, 215, 0};
	RGB M = {128, 0, 128};
	RGB G = {127, 127, 127};
	
SDL_Surface *initialize_screen(int size)
{
	SDL_Surface *ecran = NULL;
	const SDL_VideoInfo* info = NULL;
	RGB init_screen = {255, 255, 255};

	

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

	ecran = SDL_SetVideoMode(size_window, size_window+200, 24, SDL_HWSURFACE);
	/* nom de la fenêtre */
	SDL_WM_SetCaption("Jeu - Color Flood", NULL);
	/* écran tout blanc */
	fillScreen(ecran, init_screen);
	drawPalette(ecran,size);

	return ecran;
}

void initialize_text(SDL_Surface *ecran, char *nbr_coup_texte, TTF_Font *police)
{
	SDL_Rect position1, position2, position3;
	SDL_Color texteNoir = {0, 0, 0, 42};
	SDL_Color fondBlanc = {255, 255, 255, 42};
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

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

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

void drawPalette(SDL_Surface *ecran,int size)
{
	drawRectangle(ecran, (size_window-6*(size_window/size))/2,size_window+size_window/size, size_window/size, B);
	drawRectangle(ecran, (size_window-6*(size_window/size))/2+size_window/size,size_window+size_window/size, size_window/size, V);
	drawRectangle(ecran, (size_window-6*(size_window/size))/2+2*(size_window/size), size_window+size_window/size, size_window/size, R);
	drawRectangle(ecran, (size_window-6*(size_window/size))/2+3*(size_window/size), size_window+size_window/size, size_window/size, J);
	drawRectangle(ecran, (size_window-6*(size_window/size))/2+4*(size_window/size), size_window+size_window/size, size_window/size, M);
	drawRectangle(ecran, (size_window-6*(size_window/size))/2+5*(size_window/size), size_window+size_window/size, size_window/size, G);
}

int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police)
{
	int continuer = 1;
	int nbr_coup = 0;
	SDL_Surface *texte;
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42};
	SDL_Color fondBlanc = {255, 255, 255, 42};
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

			case SDL_MOUSEBUTTONUP:
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    int x,y;
                    x = event.button.x ;
                    y = event.button.y ;
                    int bpp = ecran->format->BytesPerPixel;
                    /* Here p is the address to the pixel we want to retrieve */
                    Uint8 *p = (Uint8 *)ecran->pixels + y * ecran->pitch + x * bpp;
                    fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[0], p[1], p[2]);
                }
                if (event.button.button == SDL_BUTTON_LEFT) 
                {
                	/*
                	Uint32 pixel;
					SDL_PixelFormat *fmt;
					Uint8 r,g,b;
                	pixel=getpixel(ecran,event.button.x, event.button.y);
                	fmt = ecran->format;
                	SDL_GetRGB(pixel,fmt, &r, &g, &b);
                	*/
                	int x,y;
                    x = event.button.x ;
                    y = event.button.y ;
                    int bpp = ecran->format->BytesPerPixel;
                    /* Here p is the address to the pixel we want to retrieve */
                    Uint8 *p = (Uint8 *)ecran->pixels + y * ecran->pitch + x * bpp;
                    fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[0], p[1], p[2]);
					if(G.r==p[2])
                	{
					 	if (plateau[0][0].color != 'G')
						{
							modif_color('G', plateau, size);
							nbr_coup++;
						}
						break;
				    }
                	if(R.r==p[2])
                	{
						if (plateau[0][0].color != 'R')
						{
							modif_color('R', plateau, size);
							nbr_coup++;
						}
						break;
					}
                    if(J.r==p[2])
                    {
						if (plateau[0][0].color != 'J')
						{
							modif_color('J', plateau, size);
							nbr_coup++;
						}
						break;
				    }
                    if(V.r==p[2])
                    {
					   	if (plateau[0][0].color != 'V')
						{
							modif_color('V', plateau, size);
							nbr_coup++;
						}
						break;
					}
                    if(B.r==p[2])
					{
						if (plateau[0][0].color != 'B')
						{
							modif_color('B', plateau, size);
							nbr_coup++;
						}
						break;
					}
                    if(M.r==p[2])
                    {
						if (plateau[0][0].color != 'M')
						{
							modif_color('M', plateau, size);
							nbr_coup++;
						}
						break;
					}
                }
                break;
            case SDL_MOUSEMOTION:
                break;
            
		}
			sprintf(nbr_coup_texte, "Nombre de coups : %d/%d", nbr_coup, nbr_coups_max);
			texte = TTF_RenderText_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);
			SDL_BlitSurface(texte, NULL, ecran, &position);
			display_SDL(plateau, size, ecran);
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
		sleep(5);
	}
	if (if_flood(plateau, size) == 1)
	{
		texte = TTF_RenderText_Blended(police, "WIN", texteNoir);
		position.x = 190;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(5);
	}
}

void Free_surface(SDL_Surface** textes)
{
	SDL_FreeSurface(textes[0]);
	SDL_FreeSurface(textes[1]);
	SDL_FreeSurface(textes[2]);
	SDL_FreeSurface(textes[3]);
}