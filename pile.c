#include "pile.h"


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
    Pile ret;

    ret = (Pile)malloc(sizeof(Cellule));

    ret->tete = elem;
    ret->suivant = P;

    return ret;
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



/*******************************************************************/
/***Tests unitaires ***/
/******************************************************************/

void test_est_vide(void)
{
    Pile P = NULL;

    CU_ASSERT(pile_estVide(P) == 1);
}

void test_empiler(void)
{
    Pile P = NULL;

    coordonnees couple1;
    couple1.x = 1; couple1.y = 1;


    empiler(P, couple1);

    CU_ASSERT((P->tete).x == couple1.x  &&  (P->tete).y == couple1.y);
}

void test_depiler(void)
{
    Pile P = NULL;

    coordonnees couple1, couple2, couple3;
    couple1.x = 1; couple1.y = 1;
    couple2.x = 2; couple2.y = 2;
    couple3.x = 3; couple3.y = 3;

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    P = depiler(P);

    CU_ASSERT((P->tete).x == couple2.x  &&  (P->tete).y == couple2.y);
}

void test_pile_taille(void)
{
    Pile P = NULL;

    coordonnees couple1, couple2, couple3;
    couple1.x = 1; couple1.y = 1;
    couple2.x = 2; couple2.y = 2;
    couple3.x = 3; couple3.y = 3;

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    CU_ASSERT( pile_taille(P) == 3);

    pile_vider(P);

    CU_ASSERT(pile_taille(P) == 0):
}

void test_pile_vider(void)
{
    Pile P = NULL;

    coordonnees couple1, couple2, couple3;
    couple1.x = 1; couple1.y = 1;
    couple2.x = 2; couple2.y = 2;
    couple3.x = 3; couple3.y = 3;

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    pile_vider(P);

    CU_ASSERT_PTR_NULL(P);
}
