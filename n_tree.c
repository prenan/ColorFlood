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
      struct node* tab[MAX];  //array of pointer to five childs
}Nnode,*NTree;

NTree newNTree(char c){              //create a new tree node with c 
    Nnode *n;
    n=(Nnode*)malloc(sizeof(Nnode));
    n->len=1;                         //initialize the string len as 1
    n->c=(char *)malloc(sizeof(n->len));
    n->c=&c;
    for(int i=0;i<MAX;i++)
       n->tab[i]=NULL;                //set all the children pointers as NULL
    return n;
}

NTree insert(NTree a, char c){     //from a leaf to insert  !!!not root
    
    NTree son=newNTree(c);
    for(int i=0;i<MAX;i++){
         if(a->tab[i]==NULL)
         {
         	//a->tab[i]=(Nnode*)malloc(sizeof(Nnode));
            a->tab[i]=son;           //add this new tree(string "c") as his child       
            son->len=a->len+1;        // len of string ++       
            son->c=(char *)malloc(sizeof(son->len));  //malloc bigger memomry to store new string
            son->c=strcat(a->c,&c);     //add char c at the end
            break;
        }
    }
    return son;         //return the new tree node
}

void node_delete(NTree n) {
	  if (n) {
		      assert(!n->tab[0]);
          assert(!n->tab[1]);
          assert(!n->tab[2]);
          assert(!n->tab[3]);
          assert(!n->tab[4]);
	  };
	  free(n);
}

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

bool node_isleaf(NTree n) {
	  assert(n);
	  return !node_isinner(n);
}

void tree_delete(NTree n) {
    if (n) {
        tree_delete(n->tab[0]);
        tree_delete(n->tab[1]);
        tree_delete(n->tab[2]);
        tree_delete(n->tab[3]);
        tree_delete(n->tab[4]);
        n->tab[0] = 0;
        n->tab[1] = 0;
        n->tab[2] = 0;
        n->tab[3] = 0;
        n->tab[4] = 0;
        node_delete(n);
    }
}
/*
read from the content of a node string @ *c
change the color of a plateau in order from string @ *c
when colorflood==true print string @ *c
*/
int modif_from_node(grille plateau, NTree n, int size)
{
  //assert(n);
  if(n!=NULL)
  { 
	grille copy=copie(plateau, size);   //backup original plateau to manipulate  
	for(int i=0;i<n->len;i++)           //read all the character of string of this tree node
    {
	  char ancienne_couleur=plateau[0][0];  
	  modif_color(0, 0, n->c[i], ancienne_couleur, copy, size);

	}
    if(if_flood(copy,size))  //After every time modif color if colorflood==ture
    {						 // print the current string which is a solution
      printf("Solution:");
      for(int j=0;j<n->len;j++)   //not a const char *, have to print one by one
      {
        printf("%c->",n->c[j]);
      }
      printf("\nAfter %d shots",n->len);
      return 1;           //A sulution is find return 1 not find return 0
    }
  }
  return 0;
}
/*
create a n_tree, recusively find all the solution
*/
void solution(grille plateau, NTree root, int size)
{
  //assert(root);
  if(root!=NULL)        //Not a empty tree 
  {
      int j=0;
      for(int i=0;i<MAX;i++)  //add in order the characters to the children nodes
      {
          if(color[i]!=root->c[root->len-1])  //when it's equal to parent's last color, ignore that
          {
            root->tab[j++]=insert(root,color[i]);
            modif_from_node(plateau, root->tab[j++], size); 
          }  //use all the children nodes string to try change color find colorflood
      }
      //recusively find all the children
      solution(plateau, root->tab[0], size);
      solution(plateau, root->tab[1], size);
      solution(plateau, root->tab[2], size);
      solution(plateau, root->tab[3], size);
      solution(plateau, root->tab[4], size);
      
  }
}
