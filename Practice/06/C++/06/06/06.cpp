#include <iostream>
#include <cmath>

int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "Введите 3 числа, каждое в отдельной строке" << std::endl;
	double a, b, c;
	std::cin >> a >> b >> c;
	if (a == 0) {
		if (b == 0) {
			std::cout << "Корней нет" << std::endl;
		}
		else {
			std::cout << "x = " << -c / b << std::endl;
		}
	}
	else {
		double d = b * b - 4 * a * c;
		if (d < 0)
			std::cout << "Не найдено действительных корней" << std::endl;
		else if (d == 0) {
			std::cout << "x = " << -b / (2 * a) << std::endl;
		}
		else {
			double d_sqrt{ std::sqrt(d) };
			double x1 = (-b + d_sqrt) / (2 * a);
			double x2 = (-b - d_sqrt) / (2 * a);

			std::cout << "x1 = " << x1 << std::endl;
			std::cout << "x2 = " << x2 << std::endl;
		}
	}
}