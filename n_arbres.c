#include "n_arbres.h"

#define NARBREVIDE NULL
#define MAXFILS 5

int max(int a,int b) {
	  return(a>b ? a:b);
} 

typedef struct t_narbre{
      char c;       /*the current color*/
      struct t_narbre *tabfils[MAXFILS];
      int nbFils;
}NNoeud,*NArbre;

int narbreVide(NArbre a){
    return (a==NARBREVIDE);
}

NArbre nouvelNArbre(char c){
    NNoeud *n;
    n=(NNoeud*)malloc(sizeof(NNoeud));
    n->c=c;
    for(int i=0;i<MAXFILS;i++)
       n->tabfils[i]=NULL;
    n->nbFils=0;
    return n;
}

/**
 ** @brief create a new node with initial color c
 **/

NArbre ajoutFils(NArbre a,NArbre fils){
  
    for(int i=0;i<MAXFILS;i++){
         if(a->tabfils[i]==NULL){
            a->tabfils[i]=fils;
            break;
           }
    }
    a->nbFils++;
    return a;
}

void affNArbreRec(NArbre a, int num){
     if (!narbreVide(a)) {
   //afficher les infos du noeud *a
     	printf("n%d [label=%c];\n",num,a->c);
     	if(num!=0)
	     printf("n%d -> n%c;\n",(num-1)/MAXFILS,num);
	for(int i=0;i<a->nbFils;i++)
     	     affNArbreRec(a->tabfils[i],MAXFILS*num+i+1);
    }
}

void node_delete(NArbre n) {
	  if (n) {
	  	    int i;
	  	    for(i=0;i<MAXFILS;i++)
		      assert(!n->tabfils[i]);
	  };
	  free(n);
}

/**
 **  detect if n has children
 **/

bool node_isinner(NArbre n) {
	  assert(n);
	  int i;
	  for(i=0;i<MAXFILS;i++)
      {   
         if(n->tabfils[i])
         	return true;
      }
      return false;
	  
}

/**
 ** detect if @a n is a leaf
 **/

bool node_isleaf(NArbre n) {
	  assert(n);
	  return !node_isinner(n);
}


void tree_delete(NArbre n) {
	  if (n) {
	  	int i;
	  	for (i = 0; i < MAXFILS; ++i)
	  	{
	  		tree_delete(n->tabfils[i]);
	  	}
	  	for (i = 0; i < MAXFILS; ++i)
	  	{
	  		n->tabfils[i]=0;
	  	}
		    node_delete(n);
	  }
}