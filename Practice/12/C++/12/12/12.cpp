#include <iostream>

int main()
{
	int a, b;
	b = 1;
	std::cin >> a;
	for (int count = 1; count < (a + 1); ++count)
		b = count * b;
	std::cout << b;
}