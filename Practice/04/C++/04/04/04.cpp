#include<iostream>;
int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c;
	std::cout << "Введите значения a, b" << std::endl;
	std::cin >> a >> b;
	// 1 cпособ:
	c = b;
	b = a;
	a = c;
	std::cout << "a, b = " << a << ", " << b << std::endl;
	// 2 способ:
	a = a + b;
	b = a - b;
	a = a - b;
	std::cout << "a, b = " << a << ", " << b;
}