#include "pile.h"


Pile pile_initialiser()
{
    return NULL;
}

int pile_estVide(Pile P)
{
    return (P == NULL) ? 1:0 ;
}

Pile empiler(Pile P, coordonnees elem)
{
    Pile ret;

    ret = (Pile)malloc(sizeof(Cellule));

    ret->tete = elem;
    ret->suivant = P;

    return ret;
}

Pile depiler(Pile P)
{
    if (pile_estVide(P))
        return NULL; /* on peut rien supprimer elle est déja vide */
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
    
    P = NULL; /* pile vide */
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

void pile_affichage(Pile P)
{
    while( !pile_estVide(P) )
    {
        printf("->[%d,%d]", (P->tete).x, (P->tete).y);
        P = P->suivant;
    }
    printf("\n");
}