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

void display_plateau(SDL_Surface *ecran, grille plateau, int size, int size_window, int px, int py)
{
	RGB V = {153, 255, 0};		// vert
	RGB R = {204, 0, 51};		// rouge-rose
	RGB B = {0, 102, 255};		// bleu
	RGB G = {102, 204, 204};	// bleu pastel
	RGB J = {255, 255, 102};	// jaune pastel
	RGB M = {153, 0, 255};		// violet
	size_window = size_window-size_window%size;

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
				drawSquare(ecran, j*size_window/size+px, i*size_window/size+py, (size_window-size_window%size)/size, B);
				break;

				case 'V':
				drawSquare(ecran, j*size_window/size+px, i*size_window/size+py, (size_window-size_window%size)/size, V);
				break;

				case 'R':
				drawSquare(ecran, j*size_window/size+px, i*size_window/size+py, (size_window-size_window%size)/size, R);
				break;

				case 'J':
				drawSquare(ecran, j*size_window/size+px, i*size_window/size+py, (size_window-size_window%size)/size, J);
				break;

				case 'M':
				drawSquare(ecran, j*size_window/size+px, i*size_window/size+py, (size_window-size_window%size)/size, M);
				break;

				case 'G':
				drawSquare(ecran, j*size_window/size+px, i*size_window/size+py, (size_window-size_window%size)/size, G);
				break;
			}
		}
	}
}

SDL_Surface *initialize_screen(int size_window)
{
	SDL_Surface *ecran;
	SDL_Surface *icone_menu, *icone_rejouer, *icone_solveur, *icone_annuler;
	SDL_Surface *icone_son, *icone_exit, *icone_like, *icone_donate, *icone_thor;
	RGB init_screen = {255, 255, 255};	// blanc

	ecran = SDL_SetVideoMode(2*size_window, size_window+120, 32, SDL_HWSURFACE);
	fillScreen(ecran, init_screen); // écran tout blanc
	
	icone_menu = SDL_LoadBMP("img/menu.bmp");
	icone_rejouer = SDL_LoadBMP("img/rejouer.bmp");
	icone_annuler = SDL_LoadBMP("img/annuler.bmp");
	icone_solveur = SDL_LoadBMP("img/solveur.bmp");
	icone_son = SDL_LoadBMP("img/son.bmp");
	icone_exit = SDL_LoadBMP("img/exit.bmp");
	icone_like = SDL_LoadBMP("img/like.bmp");
	icone_donate = SDL_LoadBMP("img/donate.bmp");
	icone_thor = SDL_LoadBMP("img/thorc.bmp");

	drawTexture(ecran, size_window*(3/2.0)+40, 25, icone_menu);
	drawTexture(ecran, size_window*(3/2.0)+135, 25, icone_rejouer);
	drawTexture(ecran, size_window*(3/2.0)+40, 150, icone_annuler);
	drawTexture(ecran, size_window*(3/2.0)+135, 150, icone_solveur);
	drawTexture(ecran, size_window*(3/2.0)+40, 402, icone_son);
	drawTexture(ecran, size_window*(3/2.0)+135, 400, icone_exit);
	drawTexture(ecran, 915, 560, icone_thor);
	drawTexture(ecran, 873, 561, icone_like);
	drawTexture(ecran, 855, 594, icone_donate);

	SDL_FreeSurface(icone_menu);
	SDL_FreeSurface(icone_rejouer);
	SDL_FreeSurface(icone_annuler);
	SDL_FreeSurface(icone_solveur);
	SDL_FreeSurface(icone_son);
	SDL_FreeSurface(icone_exit);
	SDL_FreeSurface(icone_like);
	SDL_FreeSurface(icone_donate);
	SDL_FreeSurface(icone_thor);

	return ecran;
}

void initialize_text(SDL_Surface *ecran, TTF_Font *police, int size, int difficulte)
{
	SDL_Surface *colorbox, *solution, *nbr_coups;
	SDL_Surface *menu, *rejouer, *annuler, *exit, *son, *choix_jeu;
	SDL_Color texteNoir = {0, 0, 0, 42};
	char choix_jeu_txt[20];
	
	if (difficulte == 1)
		sprintf(choix_jeu_txt, "Taille %2d (Facile)", size);
	if (difficulte == 2)
		sprintf(choix_jeu_txt, "Taille %2d (Normal)", size);
	if (difficulte == 3)
		sprintf(choix_jeu_txt, "Taille %2d (Expert)", size);
	
	colorbox = TTF_RenderUTF8_Blended(police, "Color Box", texteNoir);
	nbr_coups = TTF_RenderUTF8_Blended(police, "Nombre de coup(s)", texteNoir);
	menu = TTF_RenderUTF8_Blended(police, "Menu", texteNoir);
	rejouer = TTF_RenderUTF8_Blended(police, "Rejouer", texteNoir);
	annuler = TTF_RenderUTF8_Blended(police, "Annuler", texteNoir);
	solution = TTF_RenderUTF8_Blended(police, "Solution", texteNoir);
	son = TTF_RenderUTF8_Blended(police, "Son", texteNoir);
	exit = TTF_RenderUTF8_Blended(police, "Exit", texteNoir);
	choix_jeu = TTF_RenderUTF8_Blended(police, choix_jeu_txt, texteNoir);

	drawTexture(ecran, 80, 520, colorbox);
	drawTexture(ecran, 500*(3/2.0)+40, 300, nbr_coups);
	drawTexture(ecran, 797, 95, menu);
	drawTexture(ecran, 885, 95, rejouer);
	drawTexture(ecran, 786, 217, annuler);
	drawTexture(ecran, 882, 217, solution);
	drawTexture(ecran, 804, 468, son);
	drawTexture(ecran, 902, 468, exit);
	drawTexture(ecran, 405, 520, choix_jeu);
	
	SDL_FreeSurface(colorbox);
	SDL_FreeSurface(nbr_coups);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(rejouer);
	SDL_FreeSurface(annuler);
	SDL_FreeSurface(solution);
	SDL_FreeSurface(son);
	SDL_FreeSurface(exit);
	SDL_FreeSurface(choix_jeu);
}

void display_colorbox(SDL_Surface *ecran, int size_window)
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
		if (chemin[i] == 'C')
			i = nbr_coups_min;
		i++;
	}
}