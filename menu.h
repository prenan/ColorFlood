/**
 * \file menu.h
 * \brief Gestion du menu et de son affichage
 * \author THOR
 * \date mai 2017
 */

#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "grille.h"
#include "solveur.h"
#include "SDL.h"

#ifndef MENU_H
#define MENU_H


/**
 * \fn void display_niveau(int niveau, SDL_Surface *ecran, SDL_Surface **facile, SDL_Surface **normal, SDL_Surface **expert, SDL_Color couleur_texte_W, SDL_Color couleur_texte_G)
 * \brief Affichage du choix du niveau du jeu
 *
 * \param niveau Niveau du jeu choisi (1 pour facile, 2 pour normal, 3 pour expert)
 * \param ecran L'écran du menu
 * \param facile, normal, expert Pointeurs du texte correspondant
 * \param size Taille du jeu (grille size*size)
 * \param couleur_texte_W, couleur_texte_G La couleur du texte (W pour blanc, G pour gris)
 */
void display_niveau(int niveau, SDL_Surface *ecran, SDL_Surface **facile, SDL_Surface **normal, SDL_Surface **expert, SDL_Color couleur_texte_W, SDL_Color couleur_texte_G);

/**
 * \fn SDL_Surface *menu(TTF_Font *police_moyenne, TTF_Font *police_grande, int *size, int *difficulte, int *nbr_coups_max);
 * \brief Affiche un menu pour choisir la taille du jeu 
 *
 * \param police_moyenne, police_grande Différentes polices du texte
 * \param size Pointeur pour enregistrer la taille choisie
 * \param difficulte Pointeur pour enregistrer le niveau choisi
 * \param nbr_coups_max Pointeur pour enregistrer le nombre de coups du chemin le plus court trouvé
 * \return La surface, ie. l'écran de la fenêtre du menu 
 */
SDL_Surface *menu(TTF_Font *police_moyenne, TTF_Font *police_grande, int *size, int *difficulte, int *nbr_coups_max);


#endif