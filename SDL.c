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
	RGB V = {153, 255, 0}; //vert
	RGB R = {204, 0, 51};  //Rouge
	RGB B = {0, 102, 255}; //blue
	RGB G = {102, 204, 204}; //Qing
	RGB J = {255, 255, 102}; //Jeune
	RGB M = {153, 0, 255}; //M

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

SDL_Surface *menu(TTF_Font *police_moyenne, TTF_Font *police_grande, int *size, int *difficulte, int *nbr_coups_max)
{
	SDL_Surface *ecran, *nom_jeu, *taille_jeu, *niveau_jeu, *facile, *normal, *expert, *icone_plus, *icone_moins, *icone_jouer;
	SDL_Event event;
	SDL_Rect position_nom_jeu, position_taille_jeu, position_niveau_jeu, position_facile, position_normal, position_expert;
	SDL_Rect position_plus, position_moins, position_jouer;
	SDL_Color couleur_texte_W = {255, 255, 255, 42}, couleur_texte_G = {51, 51, 51, 42};

	bool flip = true;
	int continuer = 1, compteur = 3, niveau = 2;
	char compteur_txt[50];

	position_nom_jeu.x = 41;
	position_nom_jeu.y = 5;
	position_taille_jeu.x = 78;
	position_taille_jeu.y = 100;
	position_niveau_jeu.x = 125;
	position_niveau_jeu.y = 195;

	position_facile.x = 62;
	position_facile.y = 274;
	position_normal.x = 184;
	position_normal.y = 274;
	position_expert.x = 326;
	position_expert.y = 274;
	position_plus.x = 308;
	position_plus.y = 88;
	position_moins.x = 308;
	position_moins.y = 132;
	position_jouer.x = 176;
	position_jouer.y = 352;

	int background_size = 10, i = 0;
	grille plateau = random_grille(background_size);

	int size_window = 440;
	ecran = SDL_SetVideoMode(size_window, size_window, 32, SDL_HWSURFACE); /*fenêtre au début à cette taille par défaut*/
	SDL_WM_SetCaption("Menu ColorFlood", NULL);

	nom_jeu = TTF_RenderUTF8_Blended(police_grande, "ColorFlood", couleur_texte_G);

	icone_plus = SDL_LoadBMP("img/plus.bmp");
	icone_moins = SDL_LoadBMP("img/moins.bmp");
	icone_jouer = SDL_LoadBMP("img/jouer.bmp");

	int time_between_moves = 875;
	grille plateau_sol = copie(plateau,background_size);
	char* chemin = malloc(100*sizeof(char));
	chemin = solution_rapide(plateau_sol, background_size, nbr_coups_max);
	free_space(plateau_sol, background_size);
	

	Mix_Music *musique; //Création du pointeur de type Mix_Music
	musique = Mix_LoadMUS("son/musique_menu.mp3"); //Chargement de la musique
	Mix_VolumeMusic(30);
	Mix_PlayMusic(musique, -1);


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
					if(x >= 308 && x < 352)
					{
						if(y >= 88 && y < 132 && compteur < 24)
							compteur++;
						else if(y >= 132 && y < 176 && compteur > 3)
							compteur--;
						flip = true;
					}
					if(y >= 264 && y < 318)
					{
						if(x >= 44 && x < 132 )
							niveau = 1;
						else if(x >= 176 && x < 264)
							niveau = 2;
						else if(x >= 308 && x < 396)
							niveau = 3;
						flip = true;
					}
					else if(x >= 176 && x < 264 && y >= 352 && y < 440)
					{
						*size = compteur;
						*difficulte = niveau;
						continuer = 0;
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

		if(flip)
		{
			flip = false;
			display_menu(ecran, plateau, background_size, size_window);
			sprintf(compteur_txt, "Taille : %2d", compteur);
			taille_jeu = TTF_RenderUTF8_Blended(police_moyenne, compteur_txt, couleur_texte_G);
			niveau_jeu = TTF_RenderUTF8_Blended(police_moyenne, "Niveau :", couleur_texte_G);
			niveau_du_jeu (niveau, &ecran, &facile, &normal, &expert, couleur_texte_W, couleur_texte_G);
			SDL_BlitSurface(nom_jeu, NULL, ecran, &position_nom_jeu);
			SDL_BlitSurface(taille_jeu, NULL, ecran, &position_taille_jeu);
			SDL_BlitSurface(niveau_jeu, NULL, ecran, &position_niveau_jeu);
			SDL_BlitSurface(facile, NULL, ecran, &position_facile);
			SDL_BlitSurface(normal, NULL, ecran, &position_normal);
			SDL_BlitSurface(expert, NULL, ecran, &position_expert);
			SDL_BlitSurface(icone_plus, NULL, ecran, &position_plus);
			SDL_BlitSurface(icone_moins, NULL, ecran, &position_moins);
			SDL_BlitSurface(icone_jouer, NULL, ecran, &position_jouer);
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

void niveau_du_jeu(int niveau, SDL_Surface **ecran, SDL_Surface **facile, SDL_Surface **normal, SDL_Surface **expert, SDL_Color couleur_texte_W, SDL_Color couleur_texte_G)		
{
	TTF_Font *police_petite = TTF_OpenFont("orkney.ttf", 20);
	RGB G = {51, 51, 51};
	RGB W = {255, 255, 255};
	if (niveau == 1)
	{
		drawRectangle(*ecran, 264, 44, 44, G);
		drawRectangle(*ecran, 264, 88, 44, G);
		drawRectangle(*ecran, 264, 176, 44, W);
		drawRectangle(*ecran, 264, 220, 44, W);
		drawRectangle(*ecran, 264, 308, 44, W);
		drawRectangle(*ecran, 264, 352, 44, W);
		*facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_W); 
		*normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_G); 
		*expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_G); 
	}
	if (niveau == 2)
	{
		drawRectangle(*ecran, 264, 44, 44, W);
		drawRectangle(*ecran, 264, 88, 44, W);
		drawRectangle(*ecran, 264, 176, 44, G);
		drawRectangle(*ecran, 264, 220, 44, G);
		drawRectangle(*ecran, 264, 308, 44, W);
		drawRectangle(*ecran, 264, 352, 44, W);
		*facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_G); 
		*normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_W); 
		*expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_G); 
	}
	if (niveau == 3)
	{
		drawRectangle(*ecran, 264, 44, 44, W);
		drawRectangle(*ecran, 264, 88, 44, W);
		drawRectangle(*ecran, 264, 176, 44, W);
		drawRectangle(*ecran, 264, 220, 44, W);
		drawRectangle(*ecran, 264, 308, 44, G);
		drawRectangle(*ecran, 264, 352, 44, G);
		*facile = TTF_RenderUTF8_Blended(police_petite, "Facile", couleur_texte_G); 
		*normal = TTF_RenderUTF8_Blended(police_petite, "Normal", couleur_texte_G); 
		*expert = TTF_RenderUTF8_Blended(police_petite, "Expert", couleur_texte_W); 
	}
}

void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima)
{
	SDL_Rect rect;
	rect.x=px;
	rect.y=py;
	SDL_BlitSurface(ima, NULL, ecran, &rect);
	SDL_Flip(ecran);
}

SDL_Surface *initialize_screen(int size_window)
{
	SDL_Surface *ecran;
	SDL_Surface *icone_menu, *icone_rejouer, *icone_solveur, *icone_annuler, *icone_exit, *icone_like;
	SDL_Rect position_menu, position_rejouer, position_solveur, position_annuler, position_exit, position_like;
	RGB init_screen = {255,255,255};	//blanc

	position_menu.x = size_window*(3/2.0)+40;
	position_menu.y = 25;
	position_rejouer.x = size_window*(3/2.0)+135;
	position_rejouer.y = 25;
	position_solveur.x = size_window*(3/2.0)+85;
	position_solveur.y = 440;
	position_annuler.x = size_window*(3/2.0)+40;
	position_annuler.y = 150;
	position_exit.x = size_window*(3/2.0)+135;
	position_exit.y = 150;
	position_like.x = 880;
	position_like.y = 556;

	ecran = SDL_SetVideoMode(2*size_window, size_window+120, 32, SDL_HWSURFACE);
	/* nom de la fenêtre */
	SDL_WM_SetCaption("ColorFlood (THOR)", NULL);

	/* écran tout blanc */
	fillScreen(ecran, init_screen);
	
	icone_menu = SDL_LoadBMP("img/menu.bmp");
	icone_rejouer = SDL_LoadBMP("img/rejouer.bmp");
	icone_solveur = SDL_LoadBMP("img/solveur.bmp");
	icone_annuler = SDL_LoadBMP("img/annuler.bmp");
	icone_exit = SDL_LoadBMP("img/exit.bmp");
	icone_like = SDL_LoadBMP("img/donate.bmp");

	SDL_BlitSurface(icone_menu, NULL, ecran, &position_menu);
	SDL_BlitSurface(icone_rejouer, NULL, ecran, &position_rejouer);
	SDL_BlitSurface(icone_solveur, NULL, ecran, &position_solveur);
	SDL_BlitSurface(icone_annuler, NULL, ecran, &position_annuler);
	SDL_BlitSurface(icone_exit, NULL, ecran, &position_exit);
	SDL_BlitSurface(icone_like, NULL, ecran, &position_like);

	SDL_FreeSurface(icone_menu);
	SDL_FreeSurface(icone_rejouer);
	SDL_FreeSurface(icone_solveur);
	SDL_FreeSurface(icone_annuler);
	SDL_FreeSurface(icone_exit);
	SDL_FreeSurface(icone_like);

	return ecran;
}

void solveur_box(SDL_Surface *ecran, char* chemin, int nbr_coups_min)
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
}

void initialize_text(SDL_Surface *ecran, char *nbr_coups_texte, TTF_Font *police)
{
	SDL_Rect position_color_box, position_afficher_solution, position_texte_nbr_coups, position_valeur_nbr_coups;
	SDL_Rect position_menu, position_rejouer, position_annuler, position_exit;
	SDL_Color texteNoir = {0, 0, 0, 42};
	SDL_Surface *color_box, *afficher_solution, *texte_nbr_coups, *valeur_nrb_coups;
	SDL_Surface *menu, *rejouer, *annuler, *exit;

	color_box = TTF_RenderUTF8_Blended(police, "Color Box", texteNoir);
	afficher_solution = TTF_RenderUTF8_Blended(police, "Afficher une solution", texteNoir);
	texte_nbr_coups = TTF_RenderUTF8_Blended(police, "Nombre de coup(s) ", texteNoir);
	valeur_nrb_coups = TTF_RenderUTF8_Blended(police, nbr_coups_texte, texteNoir);
	menu = TTF_RenderUTF8_Blended(police, "Menu", texteNoir);
	rejouer = TTF_RenderUTF8_Blended(police, "Rejouer", texteNoir);
	annuler = TTF_RenderUTF8_Blended(police, "Annuler", texteNoir);
	exit = TTF_RenderUTF8_Blended(police, "Exit", texteNoir);

	position_color_box.x = 80;
	position_color_box.y = 520;
	position_afficher_solution.x = 770;
	position_afficher_solution.y = 520;
	position_texte_nbr_coups.x = 500*(3/2.0)+40;
	position_texte_nbr_coups.y = 300;
	position_valeur_nbr_coups.x = 500*(3/2.0)+90;
	position_valeur_nbr_coups.y = 330;

	position_menu.x = 797;
	position_menu.y = 95;
	position_rejouer.x = 885;
	position_rejouer.y = 95;
	position_annuler.x = 786;
	position_annuler.y = 217;
	position_exit.x = 901;
	position_exit.y = 217;

	SDL_BlitSurface(color_box, NULL, ecran, &position_color_box);
	SDL_BlitSurface(afficher_solution, NULL, ecran, &position_afficher_solution);
	SDL_BlitSurface(texte_nbr_coups, NULL, ecran, &position_texte_nbr_coups);
	SDL_BlitSurface(valeur_nrb_coups, NULL, ecran, &position_valeur_nbr_coups);
	SDL_BlitSurface(menu, NULL, ecran, &position_menu);
	SDL_BlitSurface(rejouer, NULL, ecran, &position_rejouer);
	SDL_BlitSurface(annuler, NULL, ecran, &position_annuler);
	SDL_BlitSurface(exit, NULL, ecran, &position_exit);
	
	SDL_FreeSurface(color_box);
	SDL_FreeSurface(afficher_solution);
	SDL_FreeSurface(texte_nbr_coups);
	SDL_FreeSurface(valeur_nrb_coups);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(rejouer);
	SDL_FreeSurface(annuler);
	SDL_FreeSurface(exit);
}

void color_box(SDL_Surface *ecran,int size_window)
{
	RGB V = {153, 255, 0}; //vert
	RGB R = {204, 0, 51};  //Rouge
	RGB B = {0, 102, 255}; //blue
	RGB G = {102, 204, 204}; //Qing
	RGB J = {255,255,102}; //Jeune
	RGB M = {153, 0, 255}; //M

	drawRectangle(ecran, size_window*(0.0/6)+20, size_window/4.0-40, (size_window-40)/6, G);
	drawRectangle(ecran, size_window*(1.0/6)+20,size_window/4.0-40, (size_window-40)/6, R);
	drawRectangle(ecran, size_window*(2.0/6)+20,size_window/4.0-40, (size_window-40)/6, J);
	drawRectangle(ecran, size_window*(3.0/6)+20,size_window/4.0-40, (size_window-40)/6, V);
	drawRectangle(ecran, size_window*(4.0/6)+20,size_window/4.0-40, (size_window-40)/6, B);
	drawRectangle(ecran, size_window*(5.0/6)+20,size_window/4.0-40, (size_window-40)/6, M);		
}

void display_SDL(SDL_Surface *ecran, grille plateau, int size, int size_window)
{
	size_window = 500-500%size;

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
			switch (couleur)
			{
				case 'B':
				drawRectangle(ecran, i*size_window/size+20, j*size_window/size+size_window*0.5-10, (size_window-size_window%size)/size, B);
				break;

				case 'V':
				drawRectangle(ecran, i*size_window/size+20, j*size_window/size+size_window*0.5-10, (size_window-size_window%size)/size, V);
				break;

				case 'R':
				drawRectangle(ecran, i*size_window/size+20, j*size_window/size+size_window*0.5-10, (size_window-size_window%size)/size, R);
				break;

				case 'J':
				drawRectangle(ecran, i*size_window/size+20, j*size_window/size+size_window*0.5-10, (size_window-size_window%size)/size, J);
				break;

				case 'M':
				drawRectangle(ecran, i*size_window/size+20, j*size_window/size+size_window*0.5-10, (size_window-size_window%size)/size, M);
				break;

				case 'G':
				drawRectangle(ecran, i*size_window/size+20, j*size_window/size+size_window*0.5-10, (size_window-size_window%size)/size, G);
				break;
			}
		}
	}
	SDL_Flip(ecran);
}

int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coups_texte, TTF_Font *police, int size_window, int* bouton, int* out)
{
	int continuer = 1, nbr_coups = 0, exit = 0, nbr_coups_min;
	char solveur_info[30], ancienne_couleur, *chemin_solveur, chemin_joueur[100];
	bool flip = true;
	grille plateau_copie = copie(plateau, size);
	grille plateau_initial = copie(plateau, size);
	SDL_Surface *valeur_nrb_coups, *texte_solveur_en_cours, *texte_solveur_fini, *texte_rectangle, *rectangle;
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42};
	SDL_Rect position_valeur_nbr_coups, position_solveur, position_texte_rectangle, position_rectangle;

	position_valeur_nbr_coups.x = 500*(3/2.0)+105;
	position_valeur_nbr_coups.y = 330;
	position_solveur.x = 80;
	position_solveur.y = 550;
	position_texte_rectangle.x = 500*(3/2.0)+40;
	position_texte_rectangle.y = 300;
	position_rectangle.x = 500*(3/2.0)+23;
	position_rectangle.y = 287;

	color_box(ecran,size_window);
	rectangle = SDL_LoadBMP("img/rectangle.bmp");

	Mix_Music *musique; //Création du pointeur de type Mix_Music
	musique = Mix_LoadMUS("son/musique_jeu.mp3"); //Chargement de la musique
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
				// solveur
				else if ((nbr_coups_max-nbr_coups) < 15 && y >= 440 && y < 505 && x >= size_window*(3/2.0)+85 && x < size_window*(3/2.0)+150)
				{	
					sprintf(solveur_info, "Solveur en cours...");
					texte_solveur_en_cours = TTF_RenderUTF8_Blended(police, solveur_info, texteNoir);
					SDL_BlitSurface(texte_solveur_en_cours, NULL, ecran, &position_solveur);
					SDL_Flip(ecran);
					chemin_solveur = solveur_perf(plateau, size, &nbr_coups_min);
					SDL_FreeSurface(texte_solveur_en_cours);
					solveur_box(ecran, chemin_solveur, nbr_coups_min);
					sprintf(solveur_info, "Solution possible :");
					texte_solveur_fini = TTF_RenderUTF8_Blended(police, solveur_info, texteNoir);
					SDL_BlitSurface(texte_solveur_fini, NULL, ecran, &position_solveur);
					SDL_Flip(ecran);
					SDL_FreeSurface(texte_solveur_fini);
					if(strlen(chemin_solveur)!=1)	/*free ssi pas un char*/
					free(chemin_solveur);
					flip = true;
				}
				else if (x >= size_window*(3/2.0)+40 && x < (size_window*(3/2.0)+104))
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
				}
				if (x >= size_window*(3/2.0)+135 && x < (size_window*(3/2.0)+199))
				{
					if (y >= 25 && y < 89) // bouton rejouer
					{
						*bouton = 2;
						exit = 1;
					}
					else if (y >= 150 && y < 214) // bouton exit
					{
						*out = 1;
						continuer = 0;
					}
				}
				else if (x >= 880 && x < 1000 && y >= 556 && y < 620) // bouton like
				{
					system("xdg-open https://facebook.com/unistra/");
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
			SDL_BlitSurface(rectangle, NULL, ecran, &position_rectangle);
			sprintf(nbr_coups_texte, "%d/%d", nbr_coups, nbr_coups_max);
			texte_rectangle = TTF_RenderUTF8_Blended(police, "Nombre de coups", texteNoir);
			valeur_nrb_coups = TTF_RenderUTF8_Blended(police, nbr_coups_texte, texteNoir);
			SDL_BlitSurface(valeur_nrb_coups, NULL, ecran, &position_valeur_nbr_coups);
			SDL_BlitSurface(texte_rectangle, NULL, ecran, &position_texte_rectangle);
			display_SDL(ecran, plateau, size, size_window);
			SDL_Flip(ecran);
			SDL_FreeSurface(valeur_nrb_coups);
		}
	}
	Mix_FreeMusic(musique);
	return nbr_coups;
}

void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups, int nbr_coups_max, TTF_Font *police)
{
	SDL_Color texteNoir = {0, 0, 0, 42};

	SDL_Surface *texte_denouement = NULL;
	SDL_Rect position_denouement;
	int victoire = if_flood(plateau, size);
	if (nbr_coups >= nbr_coups_max && victoire == 0)
	{
		texte_denouement = TTF_RenderUTF8_Blended(police, "GAME OVER", texteNoir);
		position_denouement.x = 350;
		position_denouement.y = 230;
		SDL_BlitSurface(texte_denouement, NULL, ecran, &position_denouement);
		SDL_Flip(ecran);
		sleep(3);
	}
	else if (victoire == 1 )
	{
		texte_denouement = TTF_RenderUTF8_Blended(police, "WIN", texteNoir);
		position_denouement.x = 450;
		position_denouement.y = 230;
		SDL_BlitSurface(texte_denouement, NULL, ecran, &position_denouement);
		SDL_Flip(ecran);
		sleep(3);
	}
	SDL_FreeSurface(texte_denouement);
}
