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
 * \fn void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur)
 * \brief Dessine un rectangle sur l'écran.
 *
 * \param ecran L'écran de la fenêtre en cours.
 * \param px, py Coordonnées haut, gauche du pixel.
 * \param size Taille du carré.
 * \param couleur Couleur du carré.
 */
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, RGB couleur);

/**
 * \fn void fillScreen(SDL_Surface *ecran, RGB couleur)
 * \brief Remplie l'écran entier d'une couleur et refresh.
 *
 * \param ecran L'écran de la fenêtre en cours.
 * \param couleur Couleur choisie pour l'écran.
 */
void fillScreen(SDL_Surface *ecran, RGB couleur);

/**
 * \fn SDL_Surface *menu(TTF_Font *police1, TTF_Font *police2, int *size)
 * \brief Affiche un menu pour choisir la taille du jeu 
 * \param police1 Police du texte 'indications' et sa taille
 * \param police1 Police du texte 'compteur' et sa taille
 * \param size Pointeur pour enregistrer la taille choisie 
 * \param difficulte Pointeur pour enregistrer la difficultée choisie 
 * \return La surface menu 
 */
SDL_Surface *menu(TTF_Font *police1, TTF_Font *police2, int *size, int *difficulte);

/**
 * \fn SDL_Surface *initialize_screen(int size_window)
 * \brief Initialisation de la fenêtre du jeu (après le menu)
 * \param size_window Taille de l'écran de jeu.
 * \return La surface, ie. l'écran de la fenêtre.
 */
SDL_Surface *initialize_screen(int size_window);

/**
 * \fn void initialize_text(SDL_Surface *ecran, char *nbr_coup_texte, TTF_Font *police)
 * \brief Initialisation du texte pour les règles et le nombre de coups.
 *
 * \param ecran L'écran de la fenêtre en cours.
 * \param nbr_coup_texte Le texte pour afficher le nb de coups restants.
 * \param police La police du texte et sa taille.
 */
void initialize_text(SDL_Surface *ecran, char *nbr_coup_texte, TTF_Font *police);

/**
 * \fn void display_SDL(grille plateau, int size, SDL_Surface *ecran, int size_window)
 * \brief Affichage du plateau avec SDL à partir d'une grille.
 *
 * \param ecran L'écran de la fenêtre en cours.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param size_window Taille de l'écran de jeu.
 */
void display_SDL(SDL_Surface *ecran, grille plateau, int size, int size_window);

/**
 * \fn int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police)
 * \brief Boucle du jeu.
 *
 * \param ecran L'écran de la fenêtre en cours.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param nbr_coups_max Le nombre de coups maximum autorisés.
 * \param nbr_coup_texte Le texte pour afficher le nb de coups restants.
 * \param police La police du texte et sa taille.
 * \param size_window Taille de l'écran de jeu.
 * \return Le nombre de coups en cours.
 */
int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, char *nbr_coup_texte, TTF_Font *police, int size_window);

/**
 * \fn void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police);
 * \brief Affichage lors de la fin du jeu (victoire ou défaite).
 *
 * \param ecran L'écran de la fenêtre en cours.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \param nbr_coup Le nombre de coups effectués (en cours).
 * \param nbr_coups_max Le nombre de coups maximum autorisés.
 * \param nbr_coup_texte Le texte pour afficher le nb de coups restants.
 * \param police La police du texte et sa taille.
 */
void end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police);


#endif