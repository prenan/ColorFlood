#include "SDL.h"


void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
{
	SDL_Rect rect;
	rect.y=px;
	rect.x=py;
	rect.h=rect.w=size;
	SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
}

void fillScreen(SDL_Surface *ecran, RGB couleur)
{
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);	/*MàJ de l'écran*/
}

void display_menu(SDL_Surface *ecran, grille plateau, int size, int size_window)
{
	size_window=size_window-9;

	RGB J = {153, 255, 0}; //from B
	RGB R = {204, 0, 51};  //R
	RGB G = {0, 102, 255}; //B
	RGB V = {102, 204, 204}; //Q
	RGB B = {255,255,102}; //J
	RGB M = {153, 0, 255}; //V

	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 245, 240, 240));
	int i, j;
	char couleur;

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			couleur = plateau[i][j];
			switch (couleur)
			{
				case 'B':
				drawRectangle(ecran, i*size_window/size+i*1, j*size_window/size+j*1, size_window/size, B);
				break;

				case 'V':
				drawRectangle(ecran, i*size_window/size+i*1, j*size_window/size+j*1, size_window/size, V);
				break;

				case 'R':
				drawRectangle(ecran, i*size_window/size+i*1, j*size_window/size+j*1, size_window/size, R);
				break;

				case 'J':
				drawRectangle(ecran, i*size_window/size+i*1, j*size_window/size+j*1, size_window/size, J);
				break;

				case 'M':
				drawRectangle(ecran, i*size_window/size+i*1, j*size_window/size+j*1, size_window/size, M);
				break;

				case 'G':
				drawRectangle(ecran, i*size_window/size+i*1, j*size_window/size+j*1, size_window/size, G);
				break;
			}
		}
	}
	SDL_Flip(ecran);
}

SDL_Surface *menu(TTF_Font *police1, TTF_Font *police2, TTF_Font *police3, int *size, int *difficulte, int *nbr_coups_max,bool *border_flag)
{
	SDL_Surface *ecran, *texte1, *texte2, *texte3, *texte4, *texte5, *texte6, *texte7, *texte8, *texte9,*texte10;
	SDL_Event event;
	SDL_Rect position1, position2, position3, position4, position5, position6, position7, position8, position9,position10;
	SDL_Color couleur_texte = {0, 0, 0, 42};

	char* difficulte_txt = "Facile"; 
	bool flip = true;
	int continuer = 1, compteur = 3, niveau = 1;
	char compteur_txt[50], niveau_txt[50];

	position1.x = 20;
	position1.y = 5;
	position4.x = 110;
	position4.y = 300;
	position2.x = 80;
	position2.y = 100;
	position3.x = 15;
	position3.y = 165;

	position5.x = 310;
	position5.y = 100;
	position6.x = 312;
	position6.y = 130;

	position7.x = 70;
	position7.y = 225;
	position8.x = 165;
	position8.y = 225;
	position9.x = 270;
	position9.y = 225;

	position10.x = 140;
	position10.y = 270;

	int background_size = 10, i = 0;
	grille plateau = random_grille(background_size);

	int size_window = 429;
	ecran = SDL_SetVideoMode(size_window, size_window, 32, SDL_HWSURFACE); /*fenêtre au début à cette taille par défaut*/
	display_SDL(ecran, plateau, background_size, size_window,1);
	SDL_WM_SetCaption("Menu ColorFlood", NULL);

	texte1 = TTF_RenderUTF8_Blended(police3, "ColorFlood", couleur_texte);
	texte4 = TTF_RenderUTF8_Blended(police3, "Jouer", couleur_texte);

	texte5 = TTF_RenderUTF8_Blended(police1, "+", couleur_texte);
	texte6 = TTF_RenderUTF8_Blended(police1, "-", couleur_texte);

	texte7 = TTF_RenderUTF8_Blended(police1, "Facile", couleur_texte); 
	texte8 = TTF_RenderUTF8_Blended(police1, "Normal", couleur_texte); 
	texte9 = TTF_RenderUTF8_Blended(police1, "Expert", couleur_texte); 
	texte10 = TTF_RenderUTF8_Blended(police1, "Sans border", couleur_texte); 

	int time_between_moves = 875;
	grille plateau_sol = copie(plateau,background_size);
	char* chemin = malloc(50*sizeof(char));
	chemin = solution_rapide(plateau_sol, background_size, nbr_coups_max);
	free_space(plateau_sol, background_size);

	unsigned long time = SDL_GetTicks();
	unsigned long time_next_move = time + time_between_moves;
	while(continuer)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				*size = 0;
				continuer = 0;
				break;

				case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:	/*touche échap*/
					*size = 0;
					continuer = 0;
					break;
					default:
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int x = event.button.x;
					int y = event.button.y;
					if(x >= 309 && x < 326 && y >= 100 && y < 126)
					{
						if(compteur < 24)
						{
							compteur++;
							flip = true;
						}
					}
					if(x >= 309 && x < 326 && y >= 130 && y < 155)
					{
						if(compteur > 3)
						{
							compteur--;
							flip = true;
						}
					}
					if(x >= 68 && x < 128 && y >= 220 && y < 260)
					{
						niveau = 1;
						difficulte_txt = "Facile";
						flip = true;
					}
					if(x >= 163 && x < 237 && y >= 220 && y < 260)
					{
						niveau = 2;
						difficulte_txt = "Normal";
						flip = true;
					}
					if(x >= 269 && x < 330 && y >= 220 && y < 260)
					{
						niveau = 3;
						difficulte_txt = "Expert";
						flip = true;
					}
					if(x >= 109 && x < 288 && y >= 300 && y < 388)
					{
						*size = compteur;
						*difficulte = niveau;
						continuer = 0;
					}
					position10.x = 120;
					position10.y = 270;
					if(x >= 140 && x < 260 && y >= 270 && y < 310)
					{
						*border_flag=true;
						flip = true;
						//continuer = 0;
					}
				}
			}
		}

		if(time > time_next_move)
		{
			if(if_flood(plateau, background_size) != 1)
			{
				time_next_move = time + time_between_moves;
				char couleur = chemin[i];
				i++;
				modif_color(0, 0, couleur, plateau[0][0], plateau, background_size);
			}
			else
			{
				free_space(plateau, background_size);
				free(chemin);
				i = 0;
				plateau = random_grille(background_size);
				grille plateau_sol = copie(plateau, background_size);
				chemin = solution_rapide(plateau_sol, background_size, nbr_coups_max);
				free_space(plateau_sol, background_size);
			}
			flip = true;
		}

		if(flip)
		{
			display_menu(ecran, plateau, background_size, size_window);

			flip = false;
			sprintf(compteur_txt, "Taille : %d", compteur);
			texte2 = TTF_RenderUTF8_Blended(police2, compteur_txt, couleur_texte);
			sprintf(niveau_txt, "Niveau : %s", difficulte_txt);
			texte3 = TTF_RenderUTF8_Blended(police2, niveau_txt, couleur_texte);

			SDL_BlitSurface(texte1, NULL, ecran, &position1);
			SDL_BlitSurface(texte2, NULL, ecran, &position2);
			SDL_BlitSurface(texte3, NULL, ecran, &position3);
			SDL_BlitSurface(texte4, NULL, ecran, &position4);
			SDL_BlitSurface(texte5, NULL, ecran, &position5);
			SDL_BlitSurface(texte6, NULL, ecran, &position6);
			SDL_BlitSurface(texte7, NULL, ecran, &position7);
			SDL_BlitSurface(texte8, NULL, ecran, &position8);
			SDL_BlitSurface(texte9, NULL, ecran, &position9);
			SDL_BlitSurface(texte10, NULL, ecran, &position10);
			SDL_Flip(ecran);
		}

		unsigned long new_time = SDL_GetTicks();
		unsigned long elapsed_time = new_time - time;
		if(elapsed_time < 1000/60)
		{
			SDL_Delay(1000/60 - elapsed_time);
		}
		time = new_time;
	}
	free_space(plateau, background_size);
	SDL_FreeSurface(texte1);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(texte3);
	SDL_FreeSurface(texte4);
	SDL_FreeSurface(texte5);
	SDL_FreeSurface(texte6);
	SDL_FreeSurface(texte7);
	SDL_FreeSurface(texte8);
	SDL_FreeSurface(texte9);

	return ecran;
}

void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima) {
	SDL_Rect rect;
    rect.x=px;
    rect.y=py;
	SDL_BlitSurface(ima, NULL, ecran, &rect);
	SDL_Flip(ecran);
}

SDL_Surface *initialize_screen(int size_window)
{

	SDL_Surface *ecran = NULL;
	RGB init_screen = {255,255,255};	//blanc

	ecran = SDL_SetVideoMode(2*size_window, size_window+120, 8, SDL_HWSURFACE);
	/* nom de la fenêtre */
	SDL_WM_SetCaption("ColorFlood (THOR)", NULL);

	/*
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	SDL_Surface *ima1=NULL;
	ima1 = SDL_LoadBMP("img/fond1.bmp");
	SDL_BlitSurface(ima1, NULL, ecran, &positionFond);
	*/
	
	SDL_Surface *img=SDL_LoadBMP("./home.bmp");
    drawTexture(ecran, 50, 50, img);
    SDL_FreeSurface(img);
	
	/* écran tout blanc */
	fillScreen(ecran, init_screen);
	
	return ecran;
}

void solveur_box(SDL_Surface *ecran,char* chemin,int nbr_coups_min)
{
	RGB W = {255, 255, 255}; //blanc
	RGB V = {153, 255, 0}; //vert
	RGB R = {204, 0, 51};  //Rouge
	RGB B = {0, 102, 255}; //blue
	RGB G = {102, 204, 204}; //Qing
	RGB J = {255, 255, 102}; //Jeune
	RGB M = {153, 0, 255}; //M
	int i = 0;
	drawRectangle(ecran, 550, 80, 500, W); //clear solveur
	while(i<nbr_coups_min)
	{
		if(chemin[i]=='J')
			drawRectangle(ecran,580,85+i*27,25, J);	
		if(chemin[i]=='R')
			drawRectangle(ecran,580,85+i*27,25, R);	
		if(chemin[i]=='G')
			drawRectangle(ecran,580,85+i*27,25, G);	
		if(chemin[i]=='V')
			drawRectangle(ecran,580,85+i*27,25, V);	
		if(chemin[i]=='B')
			drawRectangle(ecran,580,85+i*27,25, B);	
		if(chemin[i]=='M')
			drawRectangle(ecran,580,85+i*27,25, M);	
		i++;
	}
	i=0;
	while(i<nbr_coups_min)
	{
		dprintf(2,"%c",chemin[i]);
		i++;
	}
	printf("\n");
}

void initialize_text(SDL_Surface *ecran,char *nbr_coup_texte, TTF_Font *police)
{
	SDL_Rect position1,position2,position3,position4;
	SDL_Rect position_menu, position_rejouer;
	SDL_Color texteNoir = {0, 0, 0, 42}, fondBlanc = {255, 255, 255, 42};	/* 4ème paramètre inutile */
	SDL_Surface *texte1,*texte2,*texte3,*texte4;
	SDL_Surface *menu, *rejouer;

	texte1 = TTF_RenderUTF8_Shaded(police, "Color Box", texteNoir, fondBlanc);
	texte2 = TTF_RenderUTF8_Shaded(police, "Afficher le solveur ", texteNoir, fondBlanc);
	texte3 = TTF_RenderUTF8_Shaded(police, "Nombre de coups ", texteNoir, fondBlanc);
	texte4 = TTF_RenderUTF8_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);
	menu = TTF_RenderUTF8_Shaded(police, "Menu", texteNoir, fondBlanc);
	rejouer = TTF_RenderUTF8_Shaded(police, "Rejouer", texteNoir, fondBlanc);

	position1.x = 80;
	position1.y = 520;
	position2.x = 785;
	position2.y = 455;
	position3.x = 500*(3/2.0)+40;
	position3.y = 500/2.0;
	position4.x = 500*(3/2.0)+90;
	position4.y = 500/2.0+30;

	position_menu.x = 802;
	position_menu.y = 100;
	position_rejouer.x = 890;
	position_rejouer.y = 100;

	SDL_BlitSurface(texte1, NULL, ecran, &position1);
	SDL_BlitSurface(texte2, NULL, ecran, &position2);
	SDL_BlitSurface(texte3, NULL, ecran, &position3);
	SDL_BlitSurface(texte4, NULL, ecran, &position4);
	SDL_BlitSurface(menu, NULL, ecran, &position_menu);
	SDL_BlitSurface(rejouer, NULL, ecran, &position_rejouer);
	
	SDL_FreeSurface(texte1);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(texte3);
	SDL_FreeSurface(texte4);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(rejouer);
}

void color_box(SDL_Surface *ecran,int size_window)
{
	RGB V = {153, 255, 0}; //vert
	RGB R = {204, 0, 51};  //Rouge
	RGB B = {0, 102, 255}; //blue
	RGB G = {102, 204, 204}; //Qing
	RGB J = {255,255,102}; //Jeune
	RGB M = {153, 0, 255}; //M
	RGB solveur = {66,66,66};
	RGB menu = {100,100,100};
	RGB rejouer = {150,150,150};
	drawRectangle(ecran, size_window*(0.0/6)+20, size_window/4.0-40, (size_window-40)/6, G);
	drawRectangle(ecran, size_window*(1.0/6)+20,size_window/4.0-40, (size_window-40)/6, R);
	drawRectangle(ecran, size_window*(2.0/6)+20,size_window/4.0-40, (size_window-40)/6, J);
	drawRectangle(ecran, size_window*(3.0/6)+20,size_window/4.0-40, (size_window-40)/6, V);
	drawRectangle(ecran, size_window*(4.0/6)+20,size_window/4.0-40, (size_window-40)/6, B);
	drawRectangle(ecran, size_window*(5.0/6)+20,size_window/4.0-40, (size_window-40)/6, M);	
	drawRectangle(ecran, size_window/2.0+100,size_window*(3/2.0)+80, (size_window-40)/6, solveur);	
	drawRectangle(ecran, 25,size_window*(3/2.0)+40, (size_window-40)/6, menu);	
	drawRectangle(ecran, 25,size_window*(3/2.0)+135, (size_window-40)/6, rejouer);	
}

void display_SDL(SDL_Surface *ecran, grille plateau, int size, int size_window, bool border_flag)
{
	RGB V = {153, 255, 0}; //vert
	RGB R = {204, 0, 51};  //Rouge
	RGB B = {0, 102, 255}; //blue
	RGB G = {102, 204, 204}; //Qing
	RGB J = {255,255,102}; //Jeune
	RGB M = {153, 0, 255}; //M

	int i, j;
	char couleur;

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			couleur = plateau[i][j];
			if(border_flag==false)
				switch (couleur)
				{
					case 'B':
					drawRectangle(ecran, i*size_window/size+10+i*2, j*size_window/size+size_window*(1.0/2)+j*2-size, size_window/size, B);
					break;

					case 'V':
					drawRectangle(ecran, i*size_window/size+10+i*2, j*size_window/size+size_window*(1.0/2)+j*2-size, size_window/size, V);
					break;

					case 'R':
					drawRectangle(ecran, i*size_window/size+10+i*2, j*size_window/size+size_window*(1.0/2)+j*2-size, size_window/size, R);
					break;

					case 'J':
					drawRectangle(ecran, i*size_window/size+10+i*2, j*size_window/size+size_window*(1.0/2)+j*2-size, size_window/size, J);
					break;

					case 'M':
					drawRectangle(ecran, i*size_window/size+10+i*2, j*size_window/size+size_window*(1.0/2)+j*2-size, size_window/size, M);
					break;

					case 'G':
					drawRectangle(ecran, i*size_window/size+10+i*2, j*size_window/size+size_window*(1.0/2)+j*2-size, size_window/size, G);
					break;
				}
			else
				switch (couleur)
				{
					case 'B':
					drawRectangle(ecran, i*size_window/size+10, j*size_window/size+size_window*(1.0/2)-size, size_window/size+size_window%size, B);
					break;

					case 'V':
					drawRectangle(ecran, i*size_window/size+10, j*size_window/size+size_window*(1.0/2)-size, size_window/size+size_window%size, V);
					break;

					case 'R':
					drawRectangle(ecran, i*size_window/size+10, j*size_window/size+size_window*(1.0/2)-size, size_window/size+size_window%size, R);
					break;

					case 'J':
					drawRectangle(ecran, i*size_window/size+10, j*size_window/size+size_window*(1.0/2)-size, size_window/size+size_window%size, J);
					break;

					case 'M':
					drawRectangle(ecran, i*size_window/size+10, j*size_window/size+size_window*(1.0/2)-size, size_window/size+size_window%size, M);
					break;

					case 'G':
					drawRectangle(ecran, i*size_window/size+10, j*size_window/size+size_window*(1.0/2)-size, size_window/size+size_window%size, G);
					break;
				}
		}
	}
	SDL_Flip(ecran);
}

int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police, int size_window, bool border_flag, int* bouton, int* out)
{
	int continuer = 1, nbr_coup = 0, exit = 0;
	SDL_Surface *texte, *texte1,*texte2;
	char solveur_info[30];
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42}, fondBlanc = {245, 240, 240, 42};
	SDL_Rect position, position1;

	position.x = 500*(3/2.0)+90;
	position.y = 500/2.0+30;
	position1.x = 80;
	position1.y = 550;

	color_box(ecran,size_window);
	
	int nbr_coups_min;
	char* chemin;
	bool flip = true;
	while(if_flood(plateau, size) != 1 && nbr_coup < nbr_coups_max && continuer && exit == 0)
	{
		char ancienne_couleur = plateau[0][0];
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
			*out = 1;
			continuer = 0;
			break;

			case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x = event.button.x;
				int y = event.button.y;
				int cons=(size_window-40)/6;
				
	
				if(y >= (size_window*(0.0/6)+20) && y < (size_window*(0.0/6)+20+cons) && x >= (size_window/4.0-40) && x < (size_window/4.0-40+cons))
				{
					modif_color(0, 0, 'G', ancienne_couleur, plateau, size);
					nbr_coup++;
					flip = true;
				}
				if(y >= (size_window*(1.0/6)+20) && y < (size_window*(1.0/6)+20+cons) && x >= (size_window/4.0-40) && x < (size_window/4.0-40+cons))
				{
					modif_color(0, 0, 'R', ancienne_couleur, plateau, size);
					nbr_coup++;
					flip = true;
				}
				if(y >= (size_window*(2.0/6)+20) && y < (size_window*(2.0/6)+20+cons) && x >= (size_window/4.0-40) && x < (size_window/4.0-40+cons))
				{
					modif_color(0, 0, 'J', ancienne_couleur, plateau, size);
					nbr_coup++;
					flip = true;
				}
				if(y >= (size_window*(3.0/6)+20) && y < (size_window*(3.0/6)+20+cons) && x >= (size_window/4.0-40) && x < (size_window/4.0-40+cons))
				{
					modif_color(0, 0, 'V', ancienne_couleur, plateau, size);
					nbr_coup++;
					flip = true;
				}
				if(y >= (size_window*(4.0/6)+20) && y < (size_window*(4.0/6)+20+cons) && x >= (size_window/4.0-40) && x < (size_window/4.0-40+cons))
				{
					modif_color(0, 0, 'B', ancienne_couleur, plateau, size);
					nbr_coup++;
					flip = true;
				}
				if(y >= (size_window*(5.0/6)+20) && y < (size_window*(5.0/6)+20+cons) && x >= (size_window/4.0-40) && x < (size_window/4.0-40+cons))
				{
					modif_color(0, 0, 'M', ancienne_couleur, plateau, size);
					nbr_coup++;
					flip = true;
				}
				// solveur
				if(y >= (size_window/2.0+100) && y < (size_window/2.0+100+cons) && x >= (size_window*(3/2.0)+80) && x < (size_window*(3/2.0)+80+cons))
				{	
					sprintf(solveur_info, "Solveur en cours...");
					texte1 = TTF_RenderUTF8_Blended(police, solveur_info, texteNoir);
					SDL_BlitSurface(texte1, NULL, ecran, &position1);
					SDL_Flip(ecran);
					chemin = solveur_perf(plateau, size, &nbr_coups_min);
					SDL_FreeSurface(texte1);
					solveur_box(ecran,chemin,nbr_coups_min);
					sprintf(solveur_info, "Solution possible :");
					texte2 = TTF_RenderUTF8_Blended(police, solveur_info, texteNoir);
					SDL_BlitSurface(texte2, NULL, ecran, &position1);
					SDL_Flip(ecran);
					flip = true;
					free(chemin);
				}
				// bouton menu
				if(y >= 25 && y < (25+cons) && x >= size_window*(3/2.0)+40 && x < (size_window*(3/2.0)+40+cons))
				{
					*bouton = 1;
					exit = 1;
					break;
				}
				// bouton rejouer
				if(y >= 25 && y < (25+cons) && x >= size_window*(3/2.0)+135 && x < (size_window*(3/2.0)+135+cons))
				{
					*bouton = 2;
					exit = 1;
					break;
				}
	
			}
			break;

			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				*out = 1;
				continuer = 0;
				break;

				default:
				break;
			}
		}

		if (flip)
		{
			flip = false;
			sprintf(nbr_coup_texte, "%d/%d", nbr_coup, nbr_coups_max);
			texte = TTF_RenderUTF8_Shaded(police, nbr_coup_texte, texteNoir, fondBlanc);
			SDL_BlitSurface(texte, NULL, ecran, &position);
			display_SDL(ecran, plateau, size,size_window,border_flag);
			SDL_Flip(ecran);
			SDL_FreeSurface(texte);
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
		texte = TTF_RenderUTF8_Blended(police, "GAME OVER", texteNoir);
		position.x = 350;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(4);
	}
	if (if_flood(plateau, size) == 1)
	{
		texte = TTF_RenderUTF8_Blended(police, "WIN", texteNoir);
		position.x = 450;
		position.y = 230;
		SDL_BlitSurface(texte, NULL, ecran, &position);
		SDL_Flip(ecran);
		sleep(2);
	}
	SDL_FreeSurface(texte);
}
