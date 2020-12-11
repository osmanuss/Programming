#include <iostream>

void print_factorization(uint32_t n)
{
	if (n == 1) {
		std::cout << 1;
		return;
	}
	for (int i = 2, k = 0; i <= n; i++)
	{
		while (n%i == 0)
		{
			n /= i;
			k++;
		}
		if (k!=0) {
			std::cout << i;
			if (k!=1)
				std::cout << '^' << k;
			if (n!=1)
				std::cout << '*';
		}
		k = 0;
	}
}

int main()
{
	int n;
	std::cin >> n;
	print_factorization(n);
}