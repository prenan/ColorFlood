#include "pile.h"

Pile pile_initialiser()
{
    return NULL;
}


/*test pile vide ou pleine vrai = 1, faux = 0*/
int pile_estVide(Pile P)
{
    return (P == NULL) ? 1:0 ;
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

void pile_affichage(Pile P)
{
    while( !pile_estVide(P) )
    {
        printf("->[%d,%d]", (P->tete).x, (P->tete).y);
        P = P->suivant;
    }
    printf("\n");
}