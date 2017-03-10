#include "grille.h"

#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#ifndef SDL_H
#define SDL_H

#define size_window 500

struct RGB
{
	int r;
	int g;
	int b;
};

typedef struct RGB RGB;



SDL_Surface *initialize_screen();

void initialize_text(SDL_Surface *ecran, char *nbr_coup_texte, TTF_Font *police, SDL_Surface*** textes);

void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur);

void fillScreen(SDL_Surface *ecran, RGB couleur);

void pause1();

void display_SDL(grille plateau, int size, SDL_Surface *ecran);

void loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police, SDL_Surface *texte);

void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police, SDL_Surface** textes);

void Free_surface(SDL_Surface** textes);

#endif