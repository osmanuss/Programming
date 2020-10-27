#include <iostream>

int main()
{
	double s, l1, r1, l2, r2, x;
	std::cin >> s >> l1 >> r1 >> l2 >> r2;
	if ((r1 + r2) < s)
		std::cout << (-1);
	else
		if ((l1 + l2) > s)
			std::cout << (-1);
		else
			if (l1 + r2 - s == 0)
				std::cout << l1<< " " << r2;
			else
				if ((l1 + r2 - s) < 0)
				{
					x = l1 - (l1 + r2 - s);
					std::cout << x <<" "<< r2;
				}
				else
					if (l1 + r2 - s > 0)
					{
						x = r2 - (l1 + r2 - s);
						std::cout << l1 << " " << x;
					}
}