#include <assert.h>
#include <string.h>
#include "n_tree.h"
#include "grille.h"


#define TREEEMPTY NULL
#define MAX 5
char color[7]="BVRJMG";

 
typedef struct node{
      char *c;       /*the current color*/
      int h;         //the height information
      int len;       //the length  of this string
      struct node *tab[MAX];
}Nnode,*NTree;

NTree newNTree(char c){
    Nnode *n;
    n=(Nnode*)malloc(sizeof(Nnode));
    n->len=1;
    n->c=(char *)malloc(sizeof(n->len));
    n->c=&c;
    for(int i=0;i<MAX;i++)
       n->tab[i]=NULL;
    return n;
}

/**
 ** @brief create a new node with initial color c
 **/

NTree insert(NTree a, char c){     //from a leaf to insert  !!!not root
    
    NTree son=newNTree(c);
    for(int i=0;i<MAX;i++){
         if(a->tab[i]==NULL)
         {
            a->tab[i]=son;
            son->len=a->len+1;
            son->c=(char *)malloc(sizeof(son->len));
            son->c=strcat(a->c,&c);
            break;
        }
    }
    return son;
}

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
/*
bool node_isleaf(NTree n) {
	  assert(n);
	  return !node_isinner(n);
}


void tree_delete(NTree n) {
	  
}


void solution(grille plateau,int size)
{
    NTree root=newNTree(plateau[0][0]);
    int stop=1;
    while(stop)
    {
      int j=0;
      for(int i=0;i<MAX;i++)
      {
        if(color[i]!=root->c[root->len-1])
        {
          root->tab[j++]=insert(root,color[i]);
          stop=modif_from_node(plateau, n, size);
        }
      }
      root=node;
    }
}
*/

void solution(grille plateau, NTree root, int size)
{
  if(root)
  {
      int stop=1;
      int j=0;
      for(int i=0;i<MAX;i++)
        {
          if(color[i]!=root->c[root->len-1])
          {
            root->tab[j++]=insert(root,color[i]);
            stop=modif_from_node(plateau, root->tab[j++], size);
          }
      }
      if(!stop)
      exit(0);
      else
      {
        solution(plateau, root->tab[0], size);
        solution(plateau, root->tab[1], size);
        solution(plateau, root->tab[2], size);
        solution(plateau, root->tab[3], size);
        solution(plateau, root->tab[4], size);
      }
  }
}

int modif_from_node(grille plateau, NTree n, int size)
{
  grille copy=copie(plateau, size);
  for(int i=0;i<n->len;i++)
  {
    if(!if_flood(copy,size))
    {
      printf("Best solution:");
      for(int j=0;j<n->len;i++)
      {
        printf("%c->",n->c[j]);
      }
      printf("\n for %d shots",n->len);
      return 0;
    }
    else
    {
      char ancienne_couleur=plateau[0][0];
      modif_color(0, 0, n->c[i], ancienne_couleur, copy, size);
    }  
  }
  return 1;
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