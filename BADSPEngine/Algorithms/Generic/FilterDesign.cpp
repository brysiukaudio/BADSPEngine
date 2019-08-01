#include "FilterDesign.h"
#include <math.h>



void FilterDesign::designLPHPBQFilter(float* b, float* a, float normalizedCutOff, bool highpass)
{
	float C = tanf(M_PI*normalizedCutOff);
	float C_SQUARED;
	float SQRT_2_C;
	if (highpass)
	{
		C_SQUARED = C * C;
		SQRT_2_C = M_SQRT_2 * C;
		b[0] = 1 / (1 + SQRT_2_C + C_SQUARED);
		b[1] = -2 * b[0];
		b[2] = b[0];

		a[0] = 2 * b[0] * (C_SQUARED - 1); //a1
		a[1] = b[0] * (1 - SQRT_2_C + C_SQUARED); //a2


	}
	else
	{
		C = 1 / C;
		C_SQUARED = C * C;
		SQRT_2_C = M_SQRT_2 * C;
		b[0] = 1 / (1 + SQRT_2_C + C_SQUARED);
		b[1] = 2 * b[0];
		b[2] = b[0];

		a[0] = 2 * b[0] * (1 - C_SQUARED); //a1
		a[1] = b[0] * (1 - SQRT_2_C + C_SQUARED); //a2
	}
}

FilterDesign::FilterDesign()
{
}


FilterDesign::~FilterDesign()
{
}
