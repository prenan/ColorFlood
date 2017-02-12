#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"
#include "grille.h"

int main()
{
	grille M=init_file(15,"fichier_grille.txt");
	display(M,15);
        printf("%d\n",if_flood(M,15));       
        M=change_color(0,0,'a',M);
        display(M,15);
	return 0;
}
