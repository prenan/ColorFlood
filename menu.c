#include "menu.h"


void display_niveau(int niveau, TTF_Font *police_petite, SDL_Surface *ecran, SDL_Color couleur_texte_W, SDL_Color couleur_texte_G)		
{
	SDL_Surface *facile, *normal, *expert;
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
		facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_W); 
		normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_G); 
		expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_G); 
	}
	if (niveau == 2)	// niveau normal
	{
		drawSquare(ecran, 44, 264, 44, W);
		drawSquare(ecran, 88, 264, 44, W);
		drawSquare(ecran, 176, 264, 44, G);
		drawSquare(ecran, 220, 264, 44, G);
		drawSquare(ecran, 308, 264, 44, W);
		drawSquare(ecran, 352, 264, 44, W);
		facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_G); 
		normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_W); 
		expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_G); 
	}
	if (niveau == 3)	// niveau expert
	{
		drawSquare(ecran, 44, 264, 44, W);
		drawSquare(ecran, 88, 264, 44, W);
		drawSquare(ecran, 176, 264, 44, W);
		drawSquare(ecran, 220, 264, 44, W);
		drawSquare(ecran, 308, 264, 44, G);
		drawSquare(ecran, 352, 264, 44, G);
		facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_G); 
		normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_G); 
		expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_W); 
	}
	drawTexture(ecran, 62, 274, facile);
	drawTexture(ecran, 184, 274, normal);
	drawTexture(ecran, 326, 274, expert);
	SDL_FreeSurface(facile);
	SDL_FreeSurface(normal);
	SDL_FreeSurface(expert);
}

// menu_background()

SDL_Surface *menu(TTF_Font *police_petite, TTF_Font *police_moyenne, TTF_Font *police_grande, int *size, int *difficulte, int *nbr_coups_max)
{
	SDL_Surface *ecran, *nom_jeu, *taille_jeu, *niveau_jeu, *icone_plus, *icone_moins, *icone_jouer;
	SDL_Event event;
	SDL_Color couleur_texte_W = {255, 255, 255, 42}, couleur_texte_G = {51, 51, 51, 42};

	int continuer = 1, compteur = 3, niveau = 2, size_window = 440, background_size = 10, i = 0;
	bool flip = true;
	char compteur_txt[50];

	ecran = SDL_SetVideoMode(size_window, size_window, 32, SDL_HWSURFACE);

	nom_jeu = TTF_RenderUTF8_Blended(police_grande, "ColorFlood", couleur_texte_G);
	niveau_jeu = TTF_RenderUTF8_Blended(police_moyenne, "Niveau :", couleur_texte_G);
	icone_plus = SDL_LoadBMP("img/plus.bmp");
	icone_moins = SDL_LoadBMP("img/moins.bmp");
	icone_jouer = SDL_LoadBMP("img/jouer.bmp");

	// gestion arrière-plan "jeu" du menu
	int time_between_moves = 875;
	unsigned long time = SDL_GetTicks();
	unsigned long time_next_move = time + time_between_moves;
	grille plateau = random_grille(background_size), plateau_sol = copie(plateau, background_size);
	char *chemin = solution_rapide(plateau_sol, background_size, nbr_coups_max);
	free_space(plateau_sol, background_size);
	
	// gestion du son
	Mix_Music *background_music;
	background_music = Mix_LoadMUS("son/menu.mp3");
	Mix_VolumeMusic(30);
	Mix_PlayMusic(background_music, -1);

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
					if (x >= 308 && x < 352) // boutons plus ou moins
					{
						if (y >= 88 && y < 132 && compteur < 24)
							compteur++;
						else if (y >= 132 && y < 176 && compteur > 3)
							compteur--;
						flip = true;
					}
					if (y >= 264 && y < 318) // boutons niveau
					{
						if (x >= 44 && x < 132 )
							niveau = 1;
						else if ( x >= 176 && x < 264)
							niveau = 2;
						else if (x >= 308 && x < 396)
							niveau = 3;
						flip = true;
					}
					else if (x >= 176 && x < 264 && y >= 352 && y < 440) // bouton jouer
					{
						*size = compteur;
						*difficulte = niveau;
						continuer = 0;
					}
				}
			}
		}
		if (time > time_next_move) // gestion arrière-plan "jeu" du menu
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
				i = 0;
				plateau = random_grille(background_size);
				grille plateau_sol = copie(plateau, background_size);
				free(chemin);
				chemin = solution_rapide(plateau_sol, background_size, nbr_coups_max);
				free_space(plateau_sol, background_size);
			}
		}
		unsigned long new_time = SDL_GetTicks();
		unsigned long elapsed_time = new_time - time;
		if(elapsed_time < 1000/60)
		{
			SDL_Delay(1000/60 - elapsed_time);
		}
		time = new_time;

		if (flip)
		{
			flip = false;
			display_plateau(ecran, plateau, background_size, size_window, 0, 0);
			sprintf(compteur_txt, "Taille : %2d", compteur);
			taille_jeu = TTF_RenderUTF8_Blended(police_moyenne, compteur_txt, couleur_texte_G);
			drawTexture(ecran, 41, 5, nom_jeu);
			drawTexture(ecran, 78, 100, taille_jeu);
			drawTexture(ecran, 308, 88, icone_plus);
			drawTexture(ecran, 308, 132, icone_moins);
			drawTexture(ecran, 125, 195, niveau_jeu);
			drawTexture(ecran, 176, 352, icone_jouer);
			display_niveau(niveau, police_petite, ecran, couleur_texte_W, couleur_texte_G);
			SDL_Flip(ecran);
			SDL_FreeSurface(taille_jeu);
		}
	}
	free_space(plateau, background_size);
	free(chemin);
	SDL_FreeSurface(nom_jeu);
	SDL_FreeSurface(icone_plus);
	SDL_FreeSurface(icone_moins);
	SDL_FreeSurface(niveau_jeu);
	SDL_FreeSurface(icone_jouer);
	Mix_FreeMusic(background_music);

	return ecran;
}