#ifndef COUNT_H
#define COUNT_H

#include "fact.h"

int count(int k, int n)
{
	return fact(n) / (fact(k) * fact(n - k));
}

#endif