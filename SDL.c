#include "SDL.h"


void drawSquare(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
{
	SDL_Rect rect;
	rect.x = px;
	rect.y = py;
	rect.h = rect.w = size;
	SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
}

void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima)
{
	SDL_Rect rect;
	rect.x = px;
	rect.y = py;
	SDL_BlitSurface(ima, NULL, ecran, &rect);
}

void fillScreen(SDL_Surface *ecran, RGB couleur)
{
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b));
	SDL_Flip(ecran);	/*MàJ de l'écran*/
}

void display_menu(SDL_Surface *ecran, grille plateau, int size, int size_window)
{
	RGB V = {153, 255, 0};		// vert
	RGB R = {204, 0, 51};		// rouge-rose
	RGB B = {0, 102, 255};		// bleu
	RGB G = {102, 204, 204};	// bleu pastel
	RGB J = {255, 255, 102};	// jaune pastel
	RGB M = {153, 0, 255};		// violet

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
				drawSquare(ecran, j*size_window/size, i*size_window/size, size_window/size, B);
				break;

				case 'V':
				drawSquare(ecran, j*size_window/size, i*size_window/size, size_window/size, V);
				break;

				case 'R':
				drawSquare(ecran, j*size_window/size, i*size_window/size, size_window/size, R);
				break;

				case 'J':
				drawSquare(ecran, j*size_window/size, i*size_window/size, size_window/size, J);
				break;

				case 'M':
				drawSquare(ecran, j*size_window/size, i*size_window/size, size_window/size, M);
				break;

				case 'G':
				drawSquare(ecran, j*size_window/size, i*size_window/size, size_window/size, G);
				break;
			}
		}
	}
}

void niveau_du_jeu(int niveau, SDL_Surface *ecran, SDL_Surface **facile, SDL_Surface **normal, SDL_Surface **expert, SDL_Color couleur_texte_W, SDL_Color couleur_texte_G)		
{
	TTF_Font *police_petite = TTF_OpenFont("orkney.ttf", 20);
	RGB G = {51, 51, 51};
	RGB W = {255, 255, 255};
	if (niveau == 1)	// niveau facile
	{
		drawSquare(ecran, 44, 264, 44, G);
		drawSquare(ecran, 88, 264, 44, G);
		drawSquare(ecran, 176, 264, 44, W);
		drawSquare(ecran, 220, 264, 44, W);
		drawSquare(ecran, 308, 264, 44, W);
		drawSquare(ecran, 352, 264, 44, W);
		*facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_W); 
		*normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_G); 
		*expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_G); 
	}
	if (niveau == 2)	// niveau normal
	{
		drawSquare(ecran, 44, 264, 44, W);
		drawSquare(ecran, 88, 264, 44, W);
		drawSquare(ecran, 176, 264, 44, G);
		drawSquare(ecran, 220, 264, 44, G);
		drawSquare(ecran, 308, 264, 44, W);
		drawSquare(ecran, 352, 264, 44, W);
		*facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_G); 
		*normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_W); 
		*expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_G); 
	}
	if (niveau == 3)	// niveau expert
	{
		drawSquare(ecran, 44, 264, 44, W);
		drawSquare(ecran, 88, 264, 44, W);
		drawSquare(ecran, 176, 264, 44, W);
		drawSquare(ecran, 220, 264, 44, W);
		drawSquare(ecran, 308, 264, 44, G);
		drawSquare(ecran, 352, 264, 44, G);
		*facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_G); 
		*normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_G); 
		*expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_W); 
	}
	TTF_CloseFont(police_petite);
}

SDL_Surface *menu(TTF_Font *police_moyenne, TTF_Font *police_grande, int *size, int *difficulte, int *nbr_coups_max)
{
	SDL_Surface *ecran, *nom_jeu, *taille_jeu, *niveau_jeu, *facile, *normal, *expert, *icone_plus, *icone_moins, *icone_jouer;
	SDL_Event event;
	SDL_Color couleur_texte_W = {255, 255, 255, 42}, couleur_texte_G = {51, 51, 51, 42};

	bool flip = true;
	int continuer = 1, compteur = 3, niveau = 2, size_window = 440, background_size = 10, i = 0;
	char compteur_txt[50];

	ecran = SDL_SetVideoMode(size_window, size_window, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Menu ColorFlood", NULL);

	nom_jeu = TTF_RenderUTF8_Blended(police_grande, "ColorFlood", couleur_texte_G);
	niveau_jeu = TTF_RenderUTF8_Blended(police_moyenne, "Niveau :", couleur_texte_G);

	icone_plus = SDL_LoadBMP("img/plus.bmp");
	icone_moins = SDL_LoadBMP("img/moins.bmp");
	icone_jouer = SDL_LoadBMP("img/jouer.bmp");

	int time_between_moves = 875;
	char* chemin = malloc(100*sizeof(char));
	grille plateau = random_grille(background_size), plateau_sol = copie(plateau, background_size);
	chemin = solution_rapide(plateau_sol, background_size, nbr_coups_max);
	free_space(plateau_sol, background_size);
	
	Mix_Music *musique; // création du pointeur de type Mix_Music
	musique = Mix_LoadMUS("son/musique_menu.mp3"); // chargement de la musique
	Mix_VolumeMusic(30);
	Mix_PlayMusic(musique, -1);

	unsigned long time = SDL_GetTicks();
	unsigned long time_next_move = time + time_between_moves;
	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				*size = 0;
				continuer = 0;
				break;

				case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:	// touche échap
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
					if (x >= 308 && x < 352)
					{
						if (y >= 88 && y < 132 && compteur < 24)
							compteur++;
						else if (y >= 132 && y < 176 && compteur > 3)
							compteur--;
						flip = true;
					}
					if (y >= 264 && y < 318)
					{
						if (x >= 44 && x < 132 )
							niveau = 1;
						else if ( x >= 176 && x < 264)
							niveau = 2;
						else if (x >= 308 && x < 396)
							niveau = 3;
						flip = true;
					}
					else if (x >= 176 && x < 264 && y >= 352 && y < 440)
					{
						*size = compteur;
						*difficulte = niveau;
						continuer = 0;
					}
				}
			}
		}
		if (time > time_next_move)
		{
			if (if_flood(plateau, background_size) != 1)
			{
				time_next_move = time + time_between_moves;
				char couleur = chemin[i];
				i++;
				modif_color(0, 0, couleur, plateau[0][0], plateau, background_size);
				flip = true;
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
		}

		if (flip)
		{
			flip = false;
			display_menu(ecran, plateau, background_size, size_window);
			sprintf(compteur_txt, "Taille : %2d", compteur);
			taille_jeu = TTF_RenderUTF8_Blended(police_moyenne, compteur_txt, couleur_texte_G);
			niveau_du_jeu (niveau, ecran, &facile, &normal, &expert, couleur_texte_W, couleur_texte_G);
			drawTexture(ecran, 41, 5, nom_jeu);
			drawTexture(ecran, 78, 100, taille_jeu);
			drawTexture(ecran, 125, 195, niveau_jeu);
			drawTexture(ecran, 62, 274, facile);
			drawTexture(ecran, 184, 274, normal);
			drawTexture(ecran, 326, 274, expert);
			drawTexture(ecran, 308, 88, icone_plus);
			drawTexture(ecran, 308, 132, icone_moins);
			drawTexture(ecran, 176, 352, icone_jouer);
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
	SDL_FreeSurface(nom_jeu);
	SDL_FreeSurface(taille_jeu);
	SDL_FreeSurface(niveau_jeu);
	SDL_FreeSurface(facile);
	SDL_FreeSurface(normal);
	SDL_FreeSurface(expert);
	SDL_FreeSurface(icone_plus);
	SDL_FreeSurface(icone_moins);
	SDL_FreeSurface(icone_jouer);
	Mix_FreeMusic(musique);
	return ecran;
}

SDL_Surface *initialize_screen(int size_window)
{
	SDL_Surface *ecran;
	SDL_Surface *icone_menu, *icone_rejouer, *icone_solveur, *icone_annuler;
	SDL_Surface *icone_son, *icone_exit, *icone_like, *icone_donate;
	RGB init_screen = {255, 255, 255};	// blanc

	ecran = SDL_SetVideoMode(2*size_window, size_window+120, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("ColorFlood (THOR)", NULL); // nom de la fenêtre
	fillScreen(ecran, init_screen); // écran tout blanc
	
	icone_menu = SDL_LoadBMP("img/menu.bmp");
	icone_rejouer = SDL_LoadBMP("img/rejouer.bmp");
	icone_annuler = SDL_LoadBMP("img/annuler.bmp");
	icone_solveur = SDL_LoadBMP("img/solveur.bmp");
	icone_son = SDL_LoadBMP("img/son.bmp");
	icone_exit = SDL_LoadBMP("img/exit.bmp");
	icone_like = SDL_LoadBMP("img/like.bmp");
	icone_donate = SDL_LoadBMP("img/donate.bmp");

	drawTexture(ecran, size_window*(3/2.0)+40, 25, icone_menu);
	drawTexture(ecran, size_window*(3/2.0)+135, 25, icone_rejouer);
	drawTexture(ecran, size_window*(3/2.0)+40, 150, icone_annuler);
	drawTexture(ecran, size_window*(3/2.0)+135, 150, icone_solveur);
	drawTexture(ecran, size_window*(3/2.0)+40, 402, icone_son);
	drawTexture(ecran, size_window*(3/2.0)+135, 400, icone_exit);
	drawTexture(ecran, 875, 580, icone_like);
	drawTexture(ecran, 923, 587, icone_donate);

	SDL_FreeSurface(icone_menu);
	SDL_FreeSurface(icone_rejouer);
	SDL_FreeSurface(icone_annuler);
	SDL_FreeSurface(icone_solveur);
	SDL_FreeSurface(icone_son);
	SDL_FreeSurface(icone_exit);
	SDL_FreeSurface(icone_like);
	SDL_FreeSurface(icone_donate);

	return ecran;
}

void initialize_text(SDL_Surface *ecran, char *nbr_coups_texte, TTF_Font *police)
{
	SDL_Surface *colorbox, *solution, *nbr_coups, *valeur_nbr_coups;
	SDL_Surface *menu, *rejouer, *annuler, *exit, *son;
	SDL_Color texteNoir = {0, 0, 0, 42};

	colorbox = TTF_RenderUTF8_Blended(police, "Color Box", texteNoir);
	nbr_coups = TTF_RenderUTF8_Blended(police, "Nombre de coup(s) ", texteNoir);
	valeur_nbr_coups = TTF_RenderUTF8_Blended(police, nbr_coups_texte, texteNoir);
	menu = TTF_RenderUTF8_Blended(police, "Menu", texteNoir);
	rejouer = TTF_RenderUTF8_Blended(police, "Rejouer", texteNoir);
	annuler = TTF_RenderUTF8_Blended(police, "Annuler", texteNoir);
	solution = TTF_RenderUTF8_Blended(police, "Solution", texteNoir);
	son = TTF_RenderUTF8_Blended(police, "Son", texteNoir);
	exit = TTF_RenderUTF8_Blended(police, "Exit", texteNoir);

	drawTexture(ecran, 80, 520, colorbox);
	drawTexture(ecran, 500*(3/2.0)+40, 300, nbr_coups);
	drawTexture(ecran, 500*(3/2.0)+90, 330, valeur_nbr_coups);
	drawTexture(ecran, 797, 95, menu);
	drawTexture(ecran, 885, 95, rejouer);
	drawTexture(ecran, 786, 217, annuler);
	drawTexture(ecran, 882, 217, solution);
	drawTexture(ecran, 804, 468, son);
	drawTexture(ecran, 902, 468, exit);
	
	SDL_FreeSurface(colorbox);
	SDL_FreeSurface(nbr_coups);
	SDL_FreeSurface(valeur_nbr_coups);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(rejouer);
	SDL_FreeSurface(annuler);
	SDL_FreeSurface(solution);
	SDL_FreeSurface(son);
	SDL_FreeSurface(exit);
}

void color_box(SDL_Surface *ecran, int size_window)
{
	RGB V = {153, 255, 0};		// vert
	RGB R = {204, 0, 51};		// rouge-rose
	RGB B = {0, 102, 255};		// bleu
	RGB G = {102, 204, 204};	// bleu pastel
	RGB J = {255, 255, 102};	// jaune pastel
	RGB M = {153, 0, 255};		// violet

	drawSquare(ecran, size_window/4.0-40, size_window*(0.0/6)+20, (size_window-40)/6, G);
	drawSquare(ecran, size_window/4.0-40, size_window*(1.0/6)+20, (size_window-40)/6, R);
	drawSquare(ecran, size_window/4.0-40, size_window*(2.0/6)+20, (size_window-40)/6, J);
	drawSquare(ecran, size_window/4.0-40, size_window*(3.0/6)+20, (size_window-40)/6, V);
	drawSquare(ecran, size_window/4.0-40, size_window*(4.0/6)+20, (size_window-40)/6, B);
	drawSquare(ecran, size_window/4.0-40, size_window*(5.0/6)+20, (size_window-40)/6, M);	
}

void solveur_box(SDL_Surface *ecran, char* chemin, int nbr_coups_min)
{
	RGB W = {255, 255, 255};	//blanc
	RGB V = {153, 255, 0};		// vert
	RGB R = {204, 0, 51};		// rouge-rose
	RGB B = {0, 102, 255};		// bleu
	RGB G = {102, 204, 204};	// bleu pastel
	RGB J = {255, 255, 102};	// jaune pastel
	RGB M = {153, 0, 255};		// violet
	int i = 0;
	drawSquare(ecran, 80, 550, 500, W); // clear solveur
	while (i<nbr_coups_min)
	{
		if (chemin[i] == 'J')
			drawSquare(ecran, 85+i*27, 580, 25, J);
		if (chemin[i] == 'R')
			drawSquare(ecran, 85+i*27, 580, 25, R);
		if (chemin[i] == 'G')
			drawSquare(ecran, 85+i*27, 580, 25, G);	
		if (chemin[i] == 'V')
			drawSquare(ecran, 85+i*27, 580, 25, V);	
		if (chemin[i] == 'B')
			drawSquare(ecran, 85+i*27, 580, 25, B);	
		if (chemin[i] == 'M')
			drawSquare(ecran, 85+i*27, 580, 25, M);	
		i++;
	}
}

void display_SDL(SDL_Surface *ecran, grille plateau, int size, int size_window)
{
	RGB V = {153, 255, 0};		// vert
	RGB R = {204, 0, 51};		// rouge-rose
	RGB B = {0, 102, 255};		// bleu
	RGB G = {102, 204, 204};	// bleu pastel
	RGB J = {255, 255, 102};	// jaune pastel
	RGB M = {153, 0, 255};		// violet
	size_window = 500-500%size;	// pour éviter les bordures entre les carrées

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
				drawSquare(ecran, j*size_window/size+size_window*0.5-10, i*size_window/size+20, (size_window-size_window%size)/size, B);
				break;

				case 'V':
				drawSquare(ecran, j*size_window/size+size_window*0.5-10, i*size_window/size+20, (size_window-size_window%size)/size, V);
				break;

				case 'R':
				drawSquare(ecran, j*size_window/size+size_window*0.5-10, i*size_window/size+20, (size_window-size_window%size)/size, R);
				break;

				case 'J':
				drawSquare(ecran, j*size_window/size+size_window*0.5-10, i*size_window/size+20, (size_window-size_window%size)/size, J);
				break;

				case 'M':
				drawSquare(ecran, j*size_window/size+size_window*0.5-10, i*size_window/size+20, (size_window-size_window%size)/size, M);
				break;

				case 'G':
				drawSquare(ecran, j*size_window/size+size_window*0.5-10, i*size_window/size+20, (size_window-size_window%size)/size, G);
				break;
			}
		}
	}
	SDL_Flip(ecran);
}

int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coups_texte, TTF_Font *police, int size_window, int *bouton, int *out)
{
	int continuer = 1, nbr_coups = 0, exit = 0, nbr_coups_min, son = 1;
	char ancienne_couleur, *chemin_solveur, chemin_joueur[100];
	bool flip = true;
	grille plateau_copie = copie(plateau, size);
	grille plateau_initial = copie(plateau, size);
	SDL_Surface *valeur_nbr_coups, *solveur, *texte_rectangle, *rectangle, *icone_son;
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42};

	color_box(ecran, size_window);
	rectangle = SDL_LoadBMP("img/rectangle.bmp");
	icone_son = SDL_LoadBMP("img/son.bmp");
	texte_rectangle = TTF_RenderUTF8_Blended(police, "Nombre de coups", texteNoir);

	Mix_Music *musique; // Création du pointeur de type Mix_Music
	musique = Mix_LoadMUS("son/musique_jeu.mp3"); // Chargement de la musique
	Mix_VolumeMusic(30);
	Mix_PlayMusic(musique, -1);

	while (if_flood(plateau, size) != 1 && nbr_coups < nbr_coups_max && continuer && exit == 0)
	{
		ancienne_couleur = plateau[0][0];
		chemin_joueur[nbr_coups] = ancienne_couleur;
		chemin_joueur[nbr_coups+1] = '\0';

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
				if(x >= (size_window/4.0-40) && x < (size_window/4.0+24))
				{
					if (ancienne_couleur != 'G' && y >= (size_window*(0.0/6)+20) && y < (size_window*(0.0/6)+84))
					{
						modif_color(0, 0, 'G', ancienne_couleur, plateau, size);
						nbr_coups++;
					}
					if (ancienne_couleur != 'R' && y >= (size_window*(1.0/6)+20) && y < (size_window*(1.0/6)+84))
					{
						modif_color(0, 0, 'R', ancienne_couleur, plateau, size);
						nbr_coups++;
					}
					if (ancienne_couleur != 'J' && y >= (size_window*(2.0/6)+20) && y < (size_window*(2.0/6)+84))
					{
						modif_color(0, 0, 'J', ancienne_couleur, plateau, size);
						nbr_coups++;
					}
					if (ancienne_couleur != 'V' && y >= (size_window*(3.0/6)+20) && y < (size_window*(3.0/6)+84))
					{
						modif_color(0, 0, 'V', ancienne_couleur, plateau, size);
						nbr_coups++;
					}
					if (ancienne_couleur != 'B' && y >= (size_window*(4.0/6)+20) && y < (size_window*(4.0/6)+84))
					{
						modif_color(0, 0, 'B', ancienne_couleur, plateau, size);
						nbr_coups++;
					}
					if (ancienne_couleur != 'M' && y >= (size_window*(5.0/6)+20) && y < (size_window*(5.0/6)+84))
					{
						modif_color(0, 0, 'M', ancienne_couleur, plateau, size);
						nbr_coups++;
					}
					flip = true;
				}

				else if (x >= size_window*(3/2.0)+40 && x < (size_window*(3/2.0)+105))
				{
					if (y >= 25 && y < 89) // bouton menu
					{
						*bouton = 1;
						exit = 1;
					}
					else if (nbr_coups > 0 && y >= 150 && y < 214)// bouton annuler
					{
						chemin_joueur[nbr_coups] = '\0';
						testeur_chemins(plateau_copie, size, chemin_joueur);
						plateau = copie(plateau_copie, size);
						plateau_copie = copie(plateau_initial, size);
						nbr_coups--;
						flip = true;
					}
					else if (y >= 402 && y < 467) // bouton son
					{				
						if (son == 1)
						{
							Mix_PauseMusic();
							icone_son = SDL_LoadBMP("img/muet.bmp");
							son = 0;
						}
						else
						{
							Mix_ResumeMusic();
							icone_son = SDL_LoadBMP("img/son.bmp");
							son = 1;
						}
						flip = true;
					}
				}
				else if (x >= 875 && x < 908 && y >= 580 && y < 613) // bouton like
				{
					system("xdg-open https://facebook.com/unistra/");
				}
				else if (x >= 923 && x < 988 && y >= 587 && y < 609) // bouton like
				{
					system("xdg-open http://www.cts-strasbourg.eu/");
				}
				else if (x >= size_window*(3/2.0)+135 && x < (size_window*(3/2.0)+200))
				{
					if (y >= 25 && y < 89) // bouton rejouer
					{
						*bouton = 2;
						exit = 1;
					}
					else if (y >= 150 && y < 214 && (nbr_coups_max-nbr_coups) < 15) // bouton solution
					{
						solveur = TTF_RenderUTF8_Blended(police, "Solveur en cours...", texteNoir);
						drawTexture(ecran, 80, 550, solveur);
						SDL_Flip(ecran);

						chemin_solveur = solveur_perf(plateau, size, &nbr_coups_min);
						solveur = TTF_RenderUTF8_Blended(police, "Solution possible :", texteNoir);
						solveur_box(ecran, chemin_solveur, nbr_coups_min);

						drawTexture(ecran, 80, 550, solveur);
						drawTexture(ecran, size_window*(3/2.0)+40, 402, icone_son);
						SDL_Flip(ecran);
						SDL_FreeSurface(solveur);
						if(strlen(chemin_solveur) != 1)	// free ssi pas un char
							free(chemin_solveur);
						flip = true;
					}
					else if (y >= 400 && y < 465) // bouton exit
					{
						*out = 1;
						continuer = 0;
					}
				}
			}
			break;

			case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				*out = 1;
				continuer = 0;

				default:
				break;
			}
		}

		if (flip)
		{
			flip = false;
			drawTexture(ecran, 500*(3/2.0)+23, 287, rectangle);
			sprintf(nbr_coups_texte, "%d/%d", nbr_coups, nbr_coups_max);
			valeur_nbr_coups = TTF_RenderUTF8_Blended(police, nbr_coups_texte, texteNoir);
			drawTexture(ecran, 500*(3/2.0)+40, 300, texte_rectangle);
			drawTexture(ecran, 500*(3/2.0)+105, 330, valeur_nbr_coups);
			drawTexture(ecran, size_window*(3/2.0)+40, 402, icone_son);
			display_SDL(ecran, plateau, size, size_window);
			SDL_Flip(ecran);
			SDL_FreeSurface(valeur_nbr_coups);
		}
	}
	Mix_FreeMusic(musique);
	return nbr_coups;
}

void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups, int nbr_coups_max, TTF_Font *police)
{
	int victoire = if_flood(plateau, size);
	SDL_Surface *texte_denouement = NULL;
	SDL_Color texteNoir = {0, 0, 0, 42};

	if (nbr_coups >= nbr_coups_max && victoire == 0)
	{
		texte_denouement = TTF_RenderUTF8_Blended(police, "GAME OVER", texteNoir);
		drawTexture(ecran, 350, 230, texte_denouement);
		SDL_Flip(ecran);
		sleep(3);
	}
	else if (victoire == 1 )
	{
		texte_denouement = TTF_RenderUTF8_Blended(police, "WIN", texteNoir);
		drawTexture(ecran, 450, 230, texte_denouement);
		SDL_Flip(ecran);
		sleep(3);
	}
	SDL_FreeSurface(texte_denouement);
}