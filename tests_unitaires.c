#include "fichier.h"
#include "grille.h"
#include "pile.h"
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

/* README
 * Here the functions init_suite1 and clean_suite1 
 * are optional for us
 * We can might need rewrite them and apply to the function
 * CU_pSuite CU_add_suite(const char* strName,
                         CU_InitializeFunc pInit,
                         CU_CleanupFunc pClean);
*/
/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;
/* The suite initialization function. */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+")))
   {
      return -1;
   }
   else
   {
      return 0;
   }
}

/* The suite cleanup function. */
int clean_suite1(void)
{
   if (0 != fclose(temp_file))
   {
      return -1;
   }
   else
   {
      temp_file = NULL;
      return 0;
   }
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void testFPRINTF(void)
{
   int i1 = 10;

   if (NULL != temp_file)
   {
      CU_ASSERT(0 == fprintf(temp_file, ""));
      CU_ASSERT(2 == fprintf(temp_file, "Q\n"));
      CU_ASSERT(7 == fprintf(temp_file, "i1 = %d", i1));
   }
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void testFREAD(void)
{
   unsigned char buffer[20];

   if (NULL != temp_file)
   {
     /* Here rewind is equal to (void) fseek(File *stream, Long offset, SEEK_SET)*/
      rewind(temp_file);
      CU_ASSERT(9 == fread(buffer, sizeof(unsigned char), 20, temp_file));
      CU_ASSERT(0 == strncmp(buffer, "Q\ni1 = 10", 9));
   }
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
	pSuite_fichier = CU_add_suite("Suite_fichier");
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
    pSuite_grille = CU_add_suite("Suite_grille");
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
    pSuite_pile = CU_add_suite("Suite_pile");
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

   /* add the tests to the rightful suites */
   /* We need to test them one by one */

   /*Test all the functions of fichier.h here*/
	if (NULL == CU_add_test(pSuite_fichier, "test of YOUR_FUNCTION()", YOUR_FUNCTION)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

   /*Test all the functions of grille.h here*/
    if (NULL == CU_add_test(pSuite_grille, "test of YOUR_FUNCTION()", YOUR_FUNCTION)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

   /*Test all the functions of pile.h here*/
    if (NULL == CU_add_test(pSuite_pile, "test of YOUR_FUNCTION()", YOUR_FUNCTION)
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