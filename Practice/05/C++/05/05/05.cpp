#include<iostream>;

int main()
{
	setlocale(LC_ALL, "Russian");
	double x0, v0, t, a, answer;
	a = 9.8;
	std::cout << "Введите x0, v0, t" << std::endl;
	std::cin >> x0>> v0>> t;
	answer = x0 + (v0 * t) - (a * t * t / 2);
	std::cout << "x(t) = " << answer;
}