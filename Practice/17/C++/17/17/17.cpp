#include <iostream>
int main() {
	setlocale(LC_ALL, "Russian");
	const int f = 37;
	int n[f], x, x1 = 0, x2 = 0, a = 0;
	int r[18] = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };
	for (int i = 0; i < f; i++) {
		n[i] = 0;
	}
	while (1) 
	{
		std::cin >> x;
		if (x < 0) 
		{
			break;
		}
		else 
		{
			n[x]++;
			for (int k = 0; k < 18; k++) 
			{
				if (x == r[k]) 
				{
					x1++;
					break;
				}
				else if (k == 17) 
				{
					x2++;
				}
			}
		}
		for (int l = 0; l < f; l++) 
		{
			if (n[l] > a) 
			{
				a = n[l];
			}
		}
		for (int l = 0; l < f; l++) 
		{
			if (n[l] == a) 
			{
				std::cout << l << " ";
			}
		}
		std::cout << "\n";
		for (int l = 0; l < f; l++) 
		{
			if (n[l] == 0) 
			{
				std::cout << l << " ";
			}
		}
		std::cout << "\n" << x1 << " " << x2 << "\n";
	}
}