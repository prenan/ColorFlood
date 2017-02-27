#include "pile.h"
#include "coordonnees.h"

Pile pile_initialiser()
{
    return NULL;
}

int pile_estVide(Pile P)
{
    return (P == NULL) ? 1:0 ;
}

Pile empiler(Pile P, type_element elem)
{
    Pile ret=NULL;

    ret = (Pile)malloc(sizeof(Cellule));

    ret->tete = elem;
    ret->suivant = P;
    pile_vider(P);
    P=ret;
    free(ret);
    ret=NULL;

    return P;
}

Pile depiler(Pile P)
{
    if (pile_estVide(P))
        {
			perror(" erreur : on ne peut pas dépiler une pile vide !");
			exit(EXIT_FAILURE);
		} 
    return P->suivant;
}

void pile_vider(Pile P)
{
    Pile ancienne_premiereCellule;
    while( P != NULL) /* condition d'arret : n'importe quelle liste finit toujours par un suivant NULL*/
    {
        ancienne_premiereCellule = P; /* mémorisation de l'adresse de la premiere cellule */
        P = P->suivant ; /* passage au suivant */
        free(ancienne_premiereCellule); /* destruction de la cellule mémorisée */
    }
    
    free(P); /* pile vide */
    P=NULL;
}

int pile_taille(Pile P)
{
    int n = 0;
    while( !pile_estVide(P) )
    {
        n++;
        P = P->suivant;
    }
    return n;
}