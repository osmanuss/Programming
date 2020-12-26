#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b;
    b = 0;
    std::cin >> a;
    for (int count = 2; count < a; ++count)
    {
        if ((a % count) == 0)
            b++;
    }
    if (b > 0)
        std::cout << "Составное";
    else
        std::cout << "Простое";
}