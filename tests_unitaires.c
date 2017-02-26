#include "fichier.h"
#include "grille.h"
#include "pile.h"
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
void test_empiler(void)
{
    Pile P = NULL;

    coordonnees couple1;
    couple1.x = 1; couple1.y = 1;


    empiler(P, couple1);

    CU_ASSERT((P->tete).x == couple1.x  &&  (P->tete).y == couple1.y);

    pile_vider(P);
}

void test_depiler(void)
{
    Pile P = NULL;

    coordonnees couple1, couple2, couple3;
    couple1.x = 1; couple1.y = 1;
    couple2.x = 2; couple2.y = 2;
    couple3.x = 3; couple3.y = 3;

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    P = depiler(P);

    CU_ASSERT((P->tete).x == couple2.x  &&  (P->tete).y == couple2.y);

    pile_vider(P);

}

void test_pile_taille(void)
{
    Pile P = NULL;

    coordonnees couple1, couple2, couple3;
    couple1.x = 1; couple1.y = 1;
    couple2.x = 2; couple2.y = 2;
    couple3.x = 3; couple3.y = 3;

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

    coordonnees couple1, couple2, couple3;
    couple1.x = 1; couple1.y = 1;
    couple2.x = 2; couple2.y = 2;
    couple3.x = 3; couple3.y = 3;

    P = empiler(P, couple1);
    P = empiler(P, couple2);
    P = empiler(P, couple3);

    pile_vider(P);

    CU_ASSERT_PTR_NULL(P);
}


int main(void)
{
	CU_pSuite pSuite_fichier = NULL;
    CU_pSuite pSuite_grille = NULL;
    CU_pSuite pSuite_pile = NULL;

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
    pSuite_pile = CU_add_suite("Suite_pile",init_suite,clean_suite);
	if (NULL == pSuite_pile)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	

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

   /*
     *Test all the functions of pile.h here
   */

   
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
   

   /* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}