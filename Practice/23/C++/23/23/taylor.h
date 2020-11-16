#pragma once

#include <cmath>
#include "fact.h"

double taylor(double x, int k)
{
	double result = 0;
	double negative = -1;
	for (int n = 0; n < k; n++)
	{
		negative *= -1;
		result += negative * std::pow(x, 2 * n + 1) / fact(2 * n + 1);
	}
	return result;
}