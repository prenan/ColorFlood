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
#include "pile.h"
#include "coordonnees.h"

#ifndef GRILLE_H
#define GRILLE_H


/**
 * \struct element
 * \brief Structure d'une case du plateau
 *
 * Pour une case, on a son appartenance à la tâche ou non (int)
 * ainsi que sa couleur (char).
 */

typedef struct element element;

typedef char ** grille;

/**
 * \fn int choose_size()
 * \brief Choix de la taille.
 *
 * \return Taille du jeu, doit être comprise entre 4 et 24.
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
 * \fn grille change_color(coordonnees coord, char c, grille plateau)
 * \brief Fonction de changement de la couleur d'une case donnée.
 *
 * \param coord Coordonnée de la case.
 * \param c Couleur choisie.
 * \param plateau Grille en cours.
 * \return Grille avec changement de couleur de la case donnée.
 */
grille change_color(coordonnees coord, char c, grille plateau);

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
 * \fn void modif_color (coordonnees position, char couleur_choisie, char ancienne_couleur, grille plateau, int size)
 * \brief modifier la couleur de l'ensemble des cases où appartenance = 1  (la tache connexe)
 *
 * \param position Position de la case à modifier.
 * \param couleur_choisie Couleur choisie.
 * \param ancienne_couleur Ancienne couleur.
 * \param plateau Grille en cours.
 * \param size Taille du jeu (grille size*size).
 */
void modif_color (int x,int y, char couleur_choisie, char ancienne_couleur, grille plateau, int size);

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
