#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "grille.h"

/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*LES FONCTIONS DE BASE POUR LES PILES IMPLÉMENTER À L'AIDE DE LISTES */

typedef struct coordonnees
{
	int x;
	int y;
} coordonnees;

typedef struct liste
{
    coordonnees tete;
    struct liste *suivant;
} Cellule, *Pile;  /* Pile est un pointeur sur la tete de la liste */


/*créer une pile vide */
Pile pile_initialiser()
{
    return NULL;
}


/*test pile vide ou pleine vrai = 1, faux = 0*/
int pile_estVide(Pile P)
{
    return (P == NULL) ? 1:0 ;
}


/* Accéder au sommet de la pile */
int pile_accederSommet(Pile P, coordonnees *sommet) /*on renvoie la valeur de l'élément au sommet à la variable sommet*/
{
    if (pile_estVide(P))
        return 1; /* code d'erreur */
    *sommet = P->tete; 
    return 0; /* 0 renvoyé --> tout se passe bien ! */
}


/* Empiler : ajout d'un élément au sommet */
Pile empiler(Pile P, coordonnees elem)
{
    Pile ret;

    ret = (Pile)malloc(sizeof(Cellule));

    ret->tete = elem;
    ret->suivant = P;

    return ret;
}


/* Depiler : la fonction permet de supprimer le sommet et le récupérer dans une autre variable */
Pile depiler(Pile P)
{
    if (pile_estVide(P))
        return NULL; /* on peut rien supprimer elle est déja vide */
    return P->suivant;
}

/* vider la pile et détruire la liste pour libérer la mémoire */ 
void pile_vider(Pile P)
{
    Pile ancienne_premiereCellule;
    while( P != NULL) /* condition d'arret : n'importe quelle liste finit toujours par un suivant NULL*/
    {
        ancienne_premiereCellule = P; /* mémorisation de l'adresse de la premiere cellule */
        P = P->suivant ; /* passage au suivant */
        free(ancienne_premiereCellule); /* destruction de la cellule mémorisée */
    }
    
    P = NULL; /* pile vide */
}

/* la taille de la pile */ 
int pile_taille(Pile P)
{
    int n = 0;
    while( !pile_estVide(P) )
    {
        n = n + 1;
        P = P->suivant;
    }
    return n;
}


/***************************************************************************************************************************/

void extraire_fils(coordonnees pere, Pile P, char couleur_choisie, grille plateau, int size)
{
	int i = pere.x;
	int j = pere.y;
	char c = plateau[i][j].color;

	coordonnees fils_gauche, fils_droite, fils_haut, fils_bas;

	fils_gauche.x = i;
	fils_gauche.y = j-1;

	fils_droite.x = i;
	fils_droite.y = j+1;

	fils_haut.x = i-1;
	fils_haut.y = j;

	fils_bas.x = i+1;
	fils_bas.y = j;


	if ( j != 0 && (plateau[i][j-1] == c || plateau[i][j-1] == couleur_choisie) )
	{
		P = empiler(P, fils_gauche);
	}

	if ( j != size && (plateau[i][j+1] == c || plateau[i][j+1] == couleur_choisie) )
	{
		P = empiler(P, fils_droite);
	}

	if ( i != 0 && (plateau[i-1][j] == c || plateau[i-1][j] == couleur_choisie) )
	{
		P = empiler(P, fils_haut);
	}

	if ( i != size && (plateau[i+1][j] == c || plateau[i+1][j] == couleur_choisie) )
	{
		P = empiler(P, fils_bas);
	}
}

Pile identifier_tache(grille plateau, char couleur_choisie, int size)
{
	Pile resultat, pile_des_fils;
	coordonnees pere;

	pere.x = 0; /* on initialise le pere à la case origine qui va donner naissance à tous les fils */
	pere.y = 0;

	resultat = pile_initialiser(); /* le résultat est une pile qui contient toutes les coordonnées des cases de la tâche connexe */

	pile_des_fils = pile_initialiser(); /* un fils représente un chemin possible */
	pile_des_fils = empiler(pile_des_fils, pere);

	while( !pile_estVide(pile_des_fils) )
	{
		pere = pile_des_fils->tete;

		(plateau[pere.x][pere.y]).appartenance = 1; /* on marque bien qu'on a visité cette case et qu'elle appartient dorénavant à la tache */
		resultat = empiler(resultat, pere); /* on la rajoute dans le resultat */
		depiler(pile_des_fils); /* on la supprime de pile_des_fils */

		extraire_fils(pere, pile_des_fils, couleur_choisie, plateau, size); /* on n'oublie pas d'extraire de ce "père" anciennement "fils" de nouveaux fils éventuels */
	}
}