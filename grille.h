/**
 * \file grille.h
 * \brief Fonctions sur les grilles et définition d'une structure
 * \author THOR
 * \date février 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifndef GRILLE_H
#define GRILLE_H


typedef char ** grille;

/**
 * \fn int choose_size()
 * \brief Choix de la taille.
 *
 * \return Taille du jeu, doit être comprise entre 3 et 24.
 */
int choose_size();

/**
 * \fn grille initialize(int size)
 * \brief Fonction d'initialisation d'une grille.
 *
 * \param size Taille du jeu (grille à initialiser size*size), doit être compris entre 4 et 24.
 * \return Grille de taille size*size.
 */
grille initialize(int size);

/**
 * \fn void display(grille plateau, int size)
 * \brief Fonction d'affichage d'une grille.
 *
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \return Affichage du plateau.
 */
void display(grille plateau, int size);

/**
 * \fn grille random_grille(int size)
 * \brief Fonction d'initialisation d'une grille aléatoire.
 *
 * \param size Taille du jeu (grille à initialiser size*size), doit être compris entre 8 et 24.
 * \return Grille aléatoire de taille size*size.
 */
grille random_grille(int size);

/**
 * \fn void free_space(grille plateau, int size)
 * \brief Fonction de libération de la mémoire d'une grille.
 *
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 */
void free_space(grille plateau, int size);

/**
 * \fn bool if_flood(grille plateau, int size)
 * \brief Fonction de test de victoire.
 *
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 * \return 1 si le plateau est entièrement inondé d'une couleur (victoire), 0 sinon.
 */
bool if_flood(grille plateau, int size);

/**
 * \fn void modif_color (int x, int y, char couleur_choisie, char ancienne_couleur, grille plateau, int size)
 * \brief fait propager la couleur choisie sur la composante connexe à partir d'une case de départ (généralement pris (0,0) dans notre cas)
 *
 * \param x, y Position de la case à modifier.
 * \param couleur_choisie Couleur choisie.
 * \param ancienne_couleur Ancienne couleur.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 */
void modif_color (int x, int y, char couleur_choisie, char ancienne_couleur, grille plateau, int size);

/**
 * \fn grille copie(grille plateau, int size)
 * \brief Fonction qui copie une grille;
 *
 * \param plateau Grille que l'on souhaite modifier.
 * \param size Taille du jeu (grille size*size).
 * \return La nouvelle grille qui est égale à la grille mise en paramètre.
 */
grille copie(grille plateau, int size);


#endif