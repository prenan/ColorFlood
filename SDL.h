/**
 * \file SDL.h
 * \brief Fonctions pour la mise en place de la SDL
 * \author THOR
 * \date mars 2017
 */

#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "grille.h"
#include "solveur.h"

#ifndef SDL_H
#define SDL_H


/**
 * \struct RGB
 * \brief Structure pour la couleur d'une case
 *
 * Une couleur est composée de rouge, vert et bleu.
 */
struct RGB
{
	int r;
	int g;
	int b;
};

typedef struct RGB RGB;

/**
 * \fn void drawSquare(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
 * \brief Dessine un rectangle sur l'écran
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param px, py Coordonnées horizontale, verticale du pixel
 * \param size Taille du carré
 * \param couleur Couleur du carré
 */
void drawSquare(SDL_Surface *ecran, int px, int py, int size, RGB couleur);

/**
 * \fn void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima)
 * \brief Dessine une surface (image ou texte) sur l'écran
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param px, py Coordonnées horizontale, verticale du pixel (coin supérieur gauche)
 * \param ima Surface "à coller" sur l'écran
 */
void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima);

/**
 * \fn void fillScreen(SDL_Surface *ecran, RGB couleur)
 * \brief Remplie l'écran entier d'une couleur et refresh
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param couleur Couleur choisie pour l'écran
 */
void fillScreen(SDL_Surface *ecran, RGB couleur);

/**
 * \fn void display_plateau(SDL_Surface *ecran, grille plateau, int size, int size_window, int px, int py)
 * \brief Affichage du plateau avec SDL à partir d'une grille
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param size_window Taille de la fenêtre
 * \param px, py Coordonnées horizontale, verticale du pixel (coin supérieur gauche)
 */
void display_plateau(SDL_Surface *ecran, grille plateau, int size, int size_window, int px, int py);

/**
 * \fn SDL_Surface *initialize_screen(int size_window)
 * \brief Initialisation de la fenêtre du jeu (après le menu)
 *
 * \param size_window Taille de l'écran du jeu
 * \return La surface, ie. l'écran de la fenêtre du jeu
 */
SDL_Surface *initialize_screen(int size_window);

/**
 * \fn void initialize_text(SDL_Surface *ecran, TTF_Font *police, char *nbr_coups_texte, int size, int difficulte)
 * \brief Initialisation du texte pour les règles et le nombre de coups
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param police Police du texte
 * \param size Taille du jeu (grille size*size)
 * \param difficulte Niveau du jeu choisi (1 pour facile, 2 pour normal, 3 pour expert)
 */
void initialize_text(SDL_Surface *ecran, TTF_Font *police, int size, int difficulte);

/**
 * \fn void display_colorbox(SDL_Surface *ecran,int size_window)
 * \brief Barre latérale pour choisir la couleur pendant le jeu
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param size_window Taille de la fenêtre
 */
void display_colorbox(SDL_Surface *ecran, int size_window);

/**
 * \fn void solveur_box(SDL_Surface *ecran, char* chemin, int nbr_coups_min)
 * \brief Barre qui affiche le résultat du solveur
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param chemin Le chemin trouvé par le solveur
 * \param nbr_coups_min La longueur du chemin
 */
void solveur_box(SDL_Surface *ecran, char* chemin, int nbr_coups_min);


#endif