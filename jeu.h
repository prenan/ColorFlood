/**
 * \file jeu.h
 * \brief Gestion du jeu et de son affichage
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

#ifndef JEU_H
#define JEU_H


/**
 * \fn void game_choice(int size, int difficulte, int *nb_coups_max, int *nb_annuler)
 * \brief Modifie le nombre de coups max et le nombre d'annulations possibles en fonction du niveau choisi.
 *
 * \param size Taille du jeu (grille size*size)
 * \param difficulte Niveau choisi
 * \param nbr_coups_max Pointeur vers le nombre de coups maximum autorisés
 * \param nb_annuler Pointeur vers le nombre d'annulations possibles
 */
void game_choice(int size, int difficulte, int *nb_coups_max, int *nb_annuler);

/**
 * \fn int colorbox_choice(int nbr_coups, char ancienne_couleur, grille plateau, int size, int size_window, int y)
 * \brief Gestion du clic dans la zone de la Color Box
 *
 * \param nbr_coups Le nombre de coups en cours
 * \param ancienne_couleur Ancienne couleur
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param size_window Taille de la fenêtre
 * \param y Position verticale de la case à modifier
 * \return Le nombre de coups en cours
 */
int colorbox_choice(int nbr_coups, char ancienne_couleur, grille plateau, int size, int size_window, int y);

/**
 * \fn int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, int nb_annuler, char *nbr_coup_texte, TTF_Font *police_petite, TTF_Font *police_moyenne, int size_window, int *bouton, int *out)
 * \brief Boucle du jeu
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param nbr_coups_max Le nombre de coups maximum autorisés
 * \param nb_annuler Le nombre de retour en arrière possible (annuler)
 * \param nbr_coup_texte Le texte pour afficher le nb de coups restants
 * \param police_moyenne, police_grande Différentes polices du texte
 * \param size_window Taille de la fenêtre
 * \param bouton Pointeur pour retourner au menu pendant le jeu
 * \param out Pointeur pour sortir du jeu et du menu (= quitter)
 * \return Le nombre de coups en cours
 */
int loop_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coups_max, int nb_annuler, char *nbr_coup_texte, TTF_Font *police_petite, TTF_Font *police_moyenne, int size_window, int *bouton, int *out);

/**
 * \fn int end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police)
 * \brief Affichage lors de la fin du jeu (victoire ou défaite)
 *
 * \param ecran L'écran de la fenêtre en cours
 * \param plateau Grille en cours
 * \param size Taille du jeu (grille size*size)
 * \param nbr_coup Le nombre de coups effectués (en cours)
 * \param nbr_coups_max Le nombre de coups maximum autorisés
 * \param police Police du texte
 * \return 1 si la partie est terminée (victoire ou défaite),
 	0 sinon.
 */
int end_game(SDL_Surface *ecran, grille plateau, int size, int nbr_coup, int nbr_coups_max, TTF_Font *police);


#endif