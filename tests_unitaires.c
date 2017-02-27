#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"


int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
      return 0;
}

/*DÉBUT DES TESTS*/
void test_change_color(void)
{
	int size = 15;
	char c='B';
	coordonnees co = coord_def(0, 0);
    
	grille M = init_file(size, "fichier_grille.txt");
	grille plateau=M;
	plateau[0][0].color = c;

    CU_ASSERT_EQUAL_FATAL(change_color(co, c, M), plateau);
}

void test_if_flood(void)
{
	int size = 15;
	grille M1 = init_file(size, "fichier_grille.txt");
	CU_ASSERT_FALSE_FATAL(if_flood(M1, size));
		
	grille M2 = init_file(size, "fichier_grille_2.txt");
	CU_ASSERT_FALSE_FATAL(!if_flood(M2, size));
}

void test_est_vide(void)
{
    Pile P = NULL;

    CU_ASSERT(pile_estVide(P) == 1);
}

void test_empiler(void)
{
    Pile P = NULL;

    coordonnees couple1 = coord_def(1, 1);

    P = empiler(P, couple1);

    CU_ASSERT(coord_compare(P->tete, couple1) == 1);
}

void test_depiler(void)
{
    Pile P = NULL;

    coordonnees couple1=coord_def(1,1), couple2=coord_def(2,2), couple3=coord_def(3,3);

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    P = depiler(P);

    CU_ASSERT(coord_compare(P->tete, couple2) == 1);
}

void test_pile_taille(void)
{
    Pile P1 = NULL;
    Pile P2 = NULL;

    coordonnees couple1=coord_def(1,1), couple2=coord_def(2,2), couple3=coord_def(3,3);

    P1 = empiler(P1, couple1);
    P1 = empiler(P1, couple2);
    P1 = empiler(P1, couple3);

    CU_ASSERT(pile_taille(P1) == 3);

    CU_ASSERT(pile_taille(P2) == 0);
}

void test_test_neighbour(void)
{
	int size = 15;
	grille M = init_file(size, "fichier_grille.txt");

	M[size-1][size-2].appartenance = 1; 
	M[size-2][size-1].appartenance = 1;  

	CU_ASSERT(test_neighbour(M, coord_def(size-1, size-1), size, 'B') == 0); /* car appartenance = 1 */
	CU_ASSERT(test_neighbour(M, coord_def(size-1, size-1), size, 'V') == 0); /* car appartenance = 1 */

	CU_ASSERT(test_neighbour(M, coord_def(7,9), size, 'V') == 1); /* la couleur à la position (7,9) est 'J' ses voisins sont dans l'ordre 'V', 'R', 'V' et 'M' */
	CU_ASSERT(test_neighbour(M, coord_def(7,9), size, 'M') == 4);
	CU_ASSERT(test_neighbour(M, coord_def(7,9), size, 'R') == 2);
	CU_ASSERT(test_neighbour(M, coord_def(7,9), size, 'G') == 0); /* G n'existe pas au voisinage de la case (7,9) */
}

void test_coord_def(void)
{
	coordonnees A = coord_def(12, 27);

	CU_ASSERT(A.x == 12 && A.y == 27);
}

void test_coord_compare(void)
{
	coordonnees A = coord_def(1,1);
	coordonnees B = coord_def(1,1);
	coordonnees C = coord_def(2,2);

	CU_ASSERT(coord_compare(A, B) == 1);
	CU_ASSERT(coord_compare(A, C) == 0);
}

void test_open_file(void)
{
	CU_ASSERT(open_file("fichier_grille.txt") != -1);
	CU_ASSERT(open_file("fichier_inexistant.txt") == -1);
}

void test_size_file(void)
{
	CU_ASSERT(size_file("fichier_grille.txt") == 15);
	CU_ASSERT(size_file("fichier_grille_2.txt") == 15);
}

void test_init_file(void)
{
	int i, j, size = 15;
	grille M1 = initialize(15);

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			M1[i][j].color = 'R';
		}
	}

	grille M2 = init_file(size, "fichier_grille_2.txt");

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			CU_ASSERT(M1[i][j].color == M2[i][j].color);
		}
	}	
}

void test_export_file(void)
{
	int size = 4, i, j;
	grille M1 = random_grille(size);
	export_file(M1, size);	/*export vers un fichier plateau.txt*/
	grille M2 = init_file(size, "plateau.txt");

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			CU_ASSERT(M1[i][j].color == M2[i][j].color);
		}
	}	
}

void test_modif_color(void)
{
	int size = 15, i, j;
	grille M1 = init_file(size, "fichier_grille.txt");
	grille M2= M1;

	char couleur_choisie = 'B' ;
	modif_color( couleur_choisie, M1, size);
	modif_color( couleur_choisie, M2, size);
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			CU_ASSERT(M1[i][j].appartenance == M2[i][j].appartenance);
		}
	}	
}

void test_Deep(void)
{
	int size = 15, i, j;
	Pile P = NULL;
	coordonnees position_pere = coord_def(0, 0);

	P = empiler(P, position_pere);
	grille M1 = init_file(size, "fichier_grille.txt");
	grille M2 = M1;

	M2[1][0].appartenance=1;

	char couleur_choisie=M1[0][0].color;
	P = Deep(couleur_choisie, M1, size, position_pere, P);

	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			CU_ASSERT(M1[i][j].appartenance == M2[i][j].appartenance);
		}
	}
}
/*FIN DES TESTS*/


int main(void)
{
	CU_pSuite pSuite_fichier = NULL;
	CU_pSuite pSuite_grille = NULL;
	CU_pSuite pSuite_pile = NULL;
	CU_pSuite pSuite_coordonnees = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
	{
		return CU_get_error();
	}

	/*Tests des fonctions de grille.c*/
	pSuite_grille = CU_add_suite("Suite_grille", init_suite, clean_suite);
	if (NULL == pSuite_grille)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_grille, "test of change_color", test_change_color))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_grille, "test of if_flood", test_if_flood))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_grille, "test of test_neighbour", test_test_neighbour))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_grille, "test of test_modif_color", test_modif_color))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_grille, "test of test_Deep", test_Deep))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/*Tests des fonctions de pile.c*/
	pSuite_pile = CU_add_suite("Suite_pile", init_suite, clean_suite);
	if (NULL == pSuite_pile)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_pile, "test of empiler", test_empiler))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_pile, "test of depiler", test_depiler))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_pile, "test of pile_taille", test_pile_taille))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/*Tests des fonctions de coordonnees.c*/
	pSuite_coordonnees = CU_add_suite("Suite_coordonnees", init_suite, clean_suite);
	if (NULL == pSuite_coordonnees)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_coordonnees, "test of coord_def", test_coord_def))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_coordonnees, "test of coord_compare", test_coord_compare))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/*Tests des fonctions de fichier.c*/
	pSuite_fichier = CU_add_suite("Suite_fichier",init_suite,clean_suite);
	if (NULL == pSuite_fichier)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_fichier, "test of init_file", test_init_file))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_fichier, "test of open_file", test_open_file))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_fichier, "test of size_file", test_size_file))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_fichier, "test of export_file", test_export_file))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


	/*Exécute tous les tests en utilisant l'interface CUnit Basic*/
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
