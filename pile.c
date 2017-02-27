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

    return ret;
}

Pile depiler(Pile P)
{
    if(P == NULL)
    {
        printf("la pile est vide ");
        return NULL;
    }
    if(P->suivant == NULL)
    {
        free(P);
        return NULL;
    }

    /* on stocke l'avant dernier dans une variable temporaire
    et puis on libère le sommet */
    Pile nvSommet = P->suivant;
    free(P);

    return nvSommet;
}

void pile_vider(Pile P)
{
    Pile ancienne_premiereCellule;
    while( P != NULL) /* condition d'arrêt : n'importe quelle liste finit toujours par un suivant NULL*/
    {
        ancienne_premiereCellule = P; /* mémorisation de l'adresse de la première cellule */
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