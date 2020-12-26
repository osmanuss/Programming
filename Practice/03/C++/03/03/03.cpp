// Сначала используем int и int, потом double u double, потом вперемешку
//

#include <iostream>

int main()
{
    int a, b;
    double c, d;
    std::cout << "a - int, b - int" << std::endl;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;

    std::cout << "a - double, b - double" << std::endl;
    std::cout << "a = ";
    std::cin >> c;
    std::cout << "b = ";
    std::cin >> d;
    std::cout << "a + b = " << c + d << std::endl;
    std::cout << "a - b = " << c - d << std::endl;
    std::cout << "a * b = " << c * d << std::endl;
    std::cout << "a / b = " << c / d << std::endl;

    std::cout << "a - int, b - double" << std::endl;
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> c;
    std::cout << "a + b = " << a + c << std::endl;
    std::cout << "a - b = " << a - c << std::endl;
    std::cout << "a * b = " << a * c << std::endl;
    std::cout << "a / b = " << a / c << std::endl;

    std::cout << "a - double, b - int" << std::endl;
    std::cout << "a = ";
    std::cin >> c;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "a + b = " << c + b << std::endl;
    std::cout << "a - b = " << c - b << std::endl;
    std::cout << "a * b = " << c * b << std::endl;
    std::cout << "a / b = " << c / b << std::endl;
}