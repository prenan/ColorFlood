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
	if (A.x == B.x  &&  A.y == B.y)
	{
		return 1;
	}
	return 0;
}
