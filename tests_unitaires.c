#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include "coordonnees.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

/* README
 * Here the functions init_suite and clean_suite
 * are optional for us. They don't do anything in this example
 * We can might need rewrite them and apply to the function
 * CU_pSuite CU_add_suite(const char* strName,
                         CU_InitializeFunc pInit,
                         CU_CleanupFunc pClean);
*/

/* The suite initialization function. */
int init_suite(void)
{
  
      return 0;
}

/* The suite cleanup function. */
int clean_suite(void)
{
      return 0;

}

void test_change_color(void)
{
	int size;
	char c='B';
	coordonnees co;
	co.x=0;
	co.y=0;
    
	size = size_file("fichier_grille.txt");
	grille M = init_file(size, "fichier_grille.txt");
	grille plateau=M;
	plateau[0][0].color = c;

    CU_ASSERT_EQUAL_FATAL(change_color(co, c, M), plateau);
}

void test_if_flood(void)
{
	int size;
	size = size_file("fichier_grille.txt");
	grille M1 = init_file(size, "fichier_grille.txt");
	CU_ASSERT_FALSE_FATAL(if_flood(M1, size));
		
	size = size_file("fichier_grille_2.txt");
	grille M2 = init_file(size, "fichier_grille_2.txt");
	CU_ASSERT_FALSE_FATAL(!if_flood(M2, size));
}

/* All the functions of stack(pile)*/
/*******************************************************************/
/***Tests unitaires  ***/
/******************************************************************/

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
    Pile P = NULL;

    coordonnees couple1=coord_def(1,1), couple2=coord_def(2,2), couple3=coord_def(3,3);

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    CU_ASSERT( pile_taille(P) == 3);

    pile_vider(P);

    CU_ASSERT(pile_taille(P) == 0);
}

void test_pile_vider(void)
{
    Pile P = NULL;

    coordonnees couple1=coord_def(1,1), couple2=coord_def(2,2), couple3=coord_def(3,3); 

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    pile_vider(P);

    CU_ASSERT_PTR_NULL(P);
}

void test_test_neighbour(void)
{
	int size = size_file("fichier_grille.txt");
	grille M = init_file(size, "fichier_grille.txt");

	M[size-1][size-2].appartenance = 1; 
	M[size-2][size-1].appartenance = 1;  

	CU_ASSERT(test_neighbour(M, coord_def(size-1, size-1), size, 'B') == 0); /* car appartenance = 1 */
	CU_ASSERT(test_neighbour(M, coord_def(size-1, size-1), size, 'V') == 0); /* car appartenance = 1 */

	CU_ASSERT(test_neighbour(M, coord_def(7,9), size, 'V') == 3); /* la couleur à la position (7,9) est 'J' ses voisins sont dans l'ordre 'V', 'R', 'V' et 'M' */
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
/*fin des tests */


int main(void)
{
	CU_pSuite pSuite_fichier = NULL;
    CU_pSuite pSuite_grille = NULL;
    CU_pSuite pSuite_pile = NULL;
	CU_pSuite pSuite_coordonnees = NULL;

   /* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

   /* add three suites repectively for our three libaries */
   /* It will make us more easily to test our functions */
   /*
	pSuite_fichier = CU_add_suite("Suite_fichier",init_suite,clean_suite);
	if (NULL == pSuite_fichier)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	*/
	

   /* add the tests to the rightful suites */
   /* We need to test them one by one */

   /*
     *Test all the functions of fichier.h here
   */

   /*
	if (NULL == CU_add_test(pSuite_fichier, "test of YOUR_FUNCTION()", YOUR_FUNCTION)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
   */


   /*Test all the functions of grille.h here*/
   
    pSuite_grille = CU_add_suite("Suite_grille",init_suite,clean_suite);
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

   /*
     *Test all the functions of pile.h here
   */
    pSuite_pile = CU_add_suite("Suite_pile",init_suite,clean_suite);
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

	if (NULL == CU_add_test(pSuite_pile, "test of pile_vider", test_pile_vider))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
   
    /*
     *Test all the functions of coordonnees.h here
    */
    pSuite_pile = CU_add_suite("Suite_coordonnees",init_suite,clean_suite);
	if (NULL == pSuite_pile)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
    
	if (NULL == CU_add_test(pSuite_pile, "test of coord_def", test_coord_def))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_pile, "test of coord_compare", test_coord_compare))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
    /* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
