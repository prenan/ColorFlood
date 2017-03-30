#include "n_tree.h"

#define TREEEMPTY NULL
#define MAX 5

int max(int a,int b) {
	  return(a>b ? a:b);
} 

typedef struct NTree{
      char c;       /*the current color*/
      struct NTree *tab[MAX];
}Nnode,*NTree;

int is_empty(NTree a){
    return (a==TREEEMPTY);
}

NTree newNTree(char c){
    Nnode *n;
    n=(Nnode*)malloc(sizeof(Nnode));
    n->c=c;
    for(int i=0;i<MAX;i++)
       n->tab[i]=NULL;
    return n;
}

/**
 ** @brief create a new node with initial color c
 **/

NTree insert(NTree a, char c){
    
    NTree son=newNTree(c);
    for(int i=0;i<MAX;i++){
         if(a->tab[i]==NULL){
            a->tab[i]=son;
            break;
           }
    }
    return NTree;
}

/*
void printNTree(NTree a, int num){
     if (!NTreeVide(a)) {
   //afficher les infos du noeud *a
     	printf("n%d [label=%c];\n",num,a->c);
     	if(num!=0)
	     printf("n%d -> n%c;\n",(num-1)/MAX,num);
	for(int i=0;i<a->nbFils;i++)
     	     printNTree(a->tab[i],MAX*num+i+1);
    }
}
*/
void node_delete(NTree n) {
	  if (n) {
	  	    int i;
	  	    for(i=0;i<MAX;i++)
		      assert(!n->tab[i]);
	  };
	  free(n);
}

/**
 **  detect if n has children
 **/

bool node_isinner(NTree n) {
	  assert(n);
	  int i;
	  for(i=0;i<MAX;i++)
      {   
         if(n->tab[i])
         	return true;
      }
      return false;
	  
}

/**
 ** detect if @a n is a leaf
 **/

bool node_isleaf(NTree n) {
	  assert(n);
	  return !node_isinner(n);
}


void tree_delete(NTree n) {
	  if (n) {
	  	int i;
	  	for (i = 0; i < MAX; ++i)
	  	{
	  		tree_delete(n->tab[i]);
	  	}
	  	for (i = 0; i < MAX; ++i)
	  	{
	  		n->tab[i]=0;
	  	}
		    node_delete(n);
	  }
}

void construct_ntree(grille plateau,int size)
{
    NTree root=newNTree(plateau[0][0]);
    char color[6]="BVRJMG";
    grille tmp=copie(plateau, size);
    for(int i=0;i<MAX;i++)
    {
        NTree node=insert(root,color[i]);
        modif_color(0, 0, char couleur_choisie, ancienne_couleur, copy, size);
    }
}

/*
void sovleur(grille plateau, int size)
{
    grille copy=copie(plateau, size);
    char color[6]="BVRJMG";
    char ancienne_couleur = copy[0][0];

    NTree solveur=nouvelNTree(copy[0][0]);

    while()
    {
      for(int i=0;i<5;i++)
      {
        if(solveur->c==color[i]);
        else
        NTree fils=nouvelNTree(char c);
        for(int i=0;i<MAX;i++){
         if(a->tab[i]==NULL){
            a->tab[i]=fils;
            break;
        }
    }
    a->nbFils++;      
      }

    }
    modif_color(0, 0, char couleur_choisie, ancienne_couleur, copy, size);
}
*/