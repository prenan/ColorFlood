#include "jeu.h"


void game_choice(int size, int difficulte, int *nb_coups_max, int *nb_annuler)
{
	*nb_coups_max += 5/difficulte; //Facile = +5, Normal = +2, Expert = +1

	if (difficulte == 1)
	{
		*nb_annuler = -1;
	}
	if (difficulte == 2)
	{
		*nb_annuler = size/5 + 1;
	}
	if (difficulte == 3)
	{
		*nb_annuler = size/6;
	}
}

int colorbox_choice(int nbr_coups, char ancienne_couleur, grille plateau, int size, int size_window, int y)
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
	return nbr_coups;
}

int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, int nb_annuler, char *nbr_coups_texte, TTF_Font *police_petite, TTF_Font *police_moyenne, int size_window, int *bouton, int *out)
{
	int continuer = 1, nbr_coups = 0, exit = 0, nbr_coups_min, son = 1, end;
	char ancienne_couleur, *chemin_solveur, chemin_joueur[100], nb_annuler_txt[5];
	bool flip = true;
	grille plateau_copie = copie(plateau, size), plateau_initial = copie(plateau, size);
	SDL_Surface *valeur_nbr_coups, *solveur1, *solveur2, *texte_rectangle, *rectangle, *icone_son, *nb_annuler_surf;
	SDL_Event event;
	SDL_Color texteNoir = {0, 0, 0, 42};
	RGB W = {255, 255, 255};	// blanc

	display_colorbox(ecran, size_window);
	rectangle = SDL_LoadBMP("img/rectangle.bmp");
	icone_son = SDL_LoadBMP("img/son.bmp");
	texte_rectangle = TTF_RenderUTF8_Blended(police_petite, "Nombre de coups", texteNoir);
	sprintf(nbr_coups_texte, "%d/%d", nbr_coups, nbr_coups_max);
	if (nb_annuler != -1)
		sprintf(nb_annuler_txt, "%d", nb_annuler);
	else
		sprintf(nb_annuler_txt, "∞");

	Mix_Music *musique; // Création du pointeur de type Mix_Music
	musique = Mix_LoadMUS("son/jeu.mp3"); // Chargement de la musique
	Mix_VolumeMusic(30);
	Mix_PlayMusic(musique, -1);
	SDL_Flip(ecran);

	while (continuer && exit == 0)
	{
		ancienne_couleur = plateau[0][0];
		chemin_joueur[nbr_coups] = ancienne_couleur;
		chemin_joueur[nbr_coups+1] = '\0';

		end = end_game(ecran, plateau, size, nbr_coups, nbr_coups_max, police_moyenne);

		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
			*out = 1;
			continuer = 0;
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

			case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x = event.button.x;
				int y = event.button.y;				
				if(!end && x >= (size_window/4.0-40) && x < (size_window/4.0+24))
				{
					nbr_coups = colorbox_choice(nbr_coups, ancienne_couleur, plateau, size, size_window, y);
					flip = true;
				}

				else if (x >= size_window*(3/2.0)+40 && x < (size_window*(3/2.0)+105))
				{
					if (y >= 25 && y < 89) // bouton menu
					{
						*bouton = 1;
						exit = 1;
					}
					else if (!end && nbr_coups > 0 && y >= 150 && y < 214) // bouton annuler
					{
						if (nb_annuler > 0)
						{
							chemin_joueur[nbr_coups] = '\0';
							testeur_chemins(plateau_copie, size, chemin_joueur);
							plateau = copie(plateau_copie, size);
							plateau_copie = copie(plateau_initial, size);
							nbr_coups--;
							nb_annuler--;
							sprintf(nb_annuler_txt, "%d", nb_annuler);
							flip = true;
						}
						if (nb_annuler == -1)
						{
							chemin_joueur[nbr_coups] = '\0';
							testeur_chemins(plateau_copie, size, chemin_joueur);
							plateau = copie(plateau_copie, size);
							plateau_copie = copie(plateau_initial, size);
							nbr_coups--;
							flip = true;
						}
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
				else if (x >= 873 && x < 906 && y >= 561 && y < 594) // bouton like
					system("xdg-open https://www.facebook.com/ThorStrasbourg/");
				else if (x >= 855 && x < 920 && y >= 594 && y < 616) // bouton donate
					system("xdg-open https://goo.gl/5G3T5P");
				else if (x >= size_window*(3/2.0)+135 && x < (size_window*(3/2.0)+200))
				{
					if (y >= 25 && y < 89) // bouton rejouer
					{
						*bouton = 2;
						exit = 1;
					}
					else if (!end && y >= 150 && y < 214) // bouton solution
					{
						drawSquare(ecran, 80, 550, 500, W); // clear solveur
						if ((nbr_coups_max-nbr_coups) < 18) // solution minimale
						{
							solveur1 = TTF_RenderUTF8_Blended(police_petite, "Solveur en cours...", texteNoir);
							drawTexture(ecran, 80, 550, solveur1);
							SDL_Flip(ecran);
							SDL_FreeSurface(solveur1);

							chemin_solveur = solveur_perf(plateau, size, &nbr_coups_min);
							solveur2 = TTF_RenderUTF8_Blended(police_petite, "Solution minimale possible :", texteNoir);
							display_solveur(ecran, chemin_solveur, nbr_coups_min);
							drawTexture(ecran, 80, 550, solveur2);
							SDL_Flip(ecran);
							SDL_FreeSurface(solveur2);
							if(strlen(chemin_solveur) != 1)	// free ssi pas un char
								free(chemin_solveur);
						}
						else if ((nbr_coups_max-nbr_coups) >= 18) // solution rapide (pas forcément minimale)
						{
							grille plateau_sol = copie(plateau,size);
							chemin_solveur = solution_rapide(plateau_sol, size, &nbr_coups_min);
							free_space(plateau_sol, size);
							if (strlen(chemin_solveur) < 28)
								solveur1 = TTF_RenderUTF8_Blended(police_petite, "Solution possible :", texteNoir);
							else
							{
								chemin_solveur[28] = 'C'; 
								solveur1 = TTF_RenderUTF8_Blended(police_petite, "Solution possible (début) :", texteNoir);
							}
							display_solveur(ecran, chemin_solveur, nbr_coups_min);
							drawTexture(ecran, 80, 550, solveur1);
							SDL_Flip(ecran);
							SDL_FreeSurface(solveur1);
							if(strlen(chemin_solveur) != 1)	// free ssi pas un char
								free(chemin_solveur);
						}
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
		}

		if (flip)
		{
			flip = false;
			drawTexture(ecran, 500*(3/2.0)+23, 287, rectangle);
			sprintf(nbr_coups_texte, "%d/%d", nbr_coups, nbr_coups_max);
			valeur_nbr_coups = TTF_RenderUTF8_Blended(police_petite, nbr_coups_texte, texteNoir);
			nb_annuler_surf = TTF_RenderUTF8_Blended(police_petite, nb_annuler_txt, texteNoir);
			drawTexture(ecran, 500*(3/2.0)+40, 300, texte_rectangle);
			drawTexture(ecran, 500*(3/2.0)+105, 330, valeur_nbr_coups);
			drawTexture(ecran, size_window*(3/2.0)+40, 402, icone_son);
			drawSquare(ecran, size_window*(3/2.0)+62, 185, 20, W); //clear nb_annuler
			drawTexture(ecran, size_window*(3/2.0)+62, 185, nb_annuler_surf);
			display_plateau(ecran, plateau, size, size_window, size_window*0.5-10, 20);
			SDL_Flip(ecran);
			SDL_FreeSurface(valeur_nbr_coups);
			SDL_FreeSurface(nb_annuler_surf);
		}
	}
	free_space(plateau_copie, size);
	free_space(plateau_initial, size);
	SDL_FreeSurface(rectangle);
	SDL_FreeSurface(icone_son);
	SDL_FreeSurface(texte_rectangle);
	Mix_FreeMusic(musique);
	return nbr_coups;
}

int end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups, int nbr_coups_max, TTF_Font *police)
{
	int victoire = if_flood(plateau, size), end = 0;
	SDL_Surface *texte_denouement = NULL;
	SDL_Color texteNoir = {0, 0, 0, 42};

	if (nbr_coups >= nbr_coups_max && victoire == 0)
	{
		texte_denouement = TTF_RenderUTF8_Blended(police, "GAME OVER", texteNoir);
		drawTexture(ecran, 350, 230, texte_denouement);
		SDL_Flip(ecran);
		end = 1;
	}
	else if (victoire == 1)
	{
		texte_denouement = TTF_RenderUTF8_Blended(police, "WIN", texteNoir);
		drawTexture(ecran, 450, 230, texte_denouement);
		SDL_Flip(ecran);
		end = 1;
	}
	SDL_FreeSurface(texte_denouement);
	return end;
}