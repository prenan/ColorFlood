#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"
#include "grille.h"

int main()
{
	grille M=init_file(15,"fichier_grille.txt");
	display(M,15);
	return 0;
}