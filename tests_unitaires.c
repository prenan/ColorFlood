#include "fichier.h"
#include "grille.h"
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
void test_if_flood(void)
{
	int size = 15;
	grille M1 = init_file(size, "fichier_grille.txt");
	CU_ASSERT_FALSE_FATAL(if_flood(M1, size));
		
	grille M2 = init_file(size, "fichier_grille_2.txt");
	CU_ASSERT_FALSE_FATAL(!if_flood(M2, size));
}

void test_modif_color(void)
{
	int size = 15, i, j;
	grille M1 = init_file(size, "fichier_grille.txt");
	grille M2 = M1;

	char ancienne_couleur = M1[0][0], couleur_choisie = 'B';
	modif_color(0, 0, ancienne_couleur, couleur_choisie, M1, size);
	modif_color(0, 0, ancienne_couleur, couleur_choisie, M2, size);
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			CU_ASSERT(M1[i][j] == M2[i][j]);
		}
	}	
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
			M1[i][j] = 'R';
		}
	}

	grille M2 = init_file(size, "fichier_grille_2.txt");
	for (i=0 ; i<size ; i++)
	{
		for (j=0 ; j<size ; j++)
		{
			CU_ASSERT(M1[i][j] == M2[i][j]);
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
			CU_ASSERT(M1[i][j] == M2[i][j]);
		}
	}	
}
/*FIN DES TESTS*/

int main(void)
{
	CU_pSuite pSuite_fichier = NULL;
	CU_pSuite pSuite_grille = NULL;

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
	if (NULL == CU_add_test(pSuite_grille, "test of if_flood", test_if_flood))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (NULL == CU_add_test(pSuite_grille, "test of test_modif_color", test_modif_color))
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
