#include <iostream>
#include <math.h>

int main()
{
	double c;
	int a, b;
	c = 1;
	std::cin >> a;
	std::cin >> b;
	if (b > 0)
	{
		while (b > 0)
		{
			c *= a;
			b--;
		}
	}
	if (b == 0)
		c = 1;
	if (b < 0)
	{
		b = abs(b);
		while (b > 0)
		{
			c *= a;
			b--;
		}
		c = 1.00 / c;
	}
	std::cout << c;
}