/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*LES FONCTIONS DE BASE POUR LES PILES IMPLÉMENTÉES À L'AIDE DE LISTES */


#ifndef PILE_H
#define PILE_H

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
Pile pile_initialiser();


/*test pile vide ou pleine vrai = 1, faux = 0*/
int pile_estVide(Pile P);


/* Accéder au sommet de la pile */
int pile_accederSommet(Pile P, coordonnees *sommet); /*on renvoie la valeur de l'élément au sommet à la variable sommet*/


/* Empiler : ajout d'un élément au sommet */
Pile empiler(Pile P, coordonnees elem);


/* Depiler : la fonction permet de supprimer le sommet et le récupérer dans une autre variable */
Pile depiler(Pile P);

/* vider la pile et détruire la liste pour libérer la mémoire */ 
void pile_vider(Pile P);

/* la taille de la pile */ 
int pile_taille(Pile P);

/*affichage*/
void pile_affichage(Pile P);



#endif
