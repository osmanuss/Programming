#include <iostream>

int main()
{
    double a, b, c;
    char d;
    std::cin >> a >> d >> b;
    if (d == '+')
        c = a + b;
    if (d == '-')
        c = a - b;
    if (d == '*')
        c = a * b;
    if (d == '/')
        c = a / b;
    std::cout << c;
}