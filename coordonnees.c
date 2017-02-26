
#include "coordonnees.h"


coordonnees coord_def(int i, int j)
{
	coordonnees A;

	A.x = i;
	A.y = j;

	return A;
}

int coord_compare(coordonnees A, coordonnees B)
{
	if ( A.x == B.x  &&  A.y == B.y )
		return 1;
	return 0;
}


/*******************************************************************/
/***Tests unitaires ***/
/******************************************************************/

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