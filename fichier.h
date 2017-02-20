/**
 * \file fichier.h
 * \brief Fonctions sur les fichiers (ouverture etc.)
 * \author THOR
 * \date février 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "grille.h"

#ifndef FICHIER_H
#define FICHIER_H

/**
 * \fn int open_file(char const* file_name)
 * \brief Fonction d'ouverture d'un fichier.
 *
 * \param file_name Nom du fichier avec son extension.
 * \return -1 si erreur à l'ouverture, autre valeur sinon.
 */
int open_file(char const* file_name);

/**
 * \fn void close_file(int file_in)
 * \brief Fonction de fermeture d'un fichier.
 *
 * \param file_in Fichier à fermer.
 * \return ??.
 */
void close_file(int file_in);

/**
 * \fn int size_file(char* file_name)
 * \brief Fonction qui détermine la taille du jeu.
 *
 * \param file_name Nom du fichier avec son extension.
 * \return -1 si erreur dans le contenu du fichier, la valeur de la taille sinon.
 */
int size_file(char* file_name); /*check files content and return game size if ok*/
grille init_file(int size, char* file_name);
void export_file(grille plateau, int size);


#endif
