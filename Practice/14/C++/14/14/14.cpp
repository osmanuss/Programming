#include <iostream>

int main()
{
    int a, b, c;
    c = 0;
    b = 1;
    std::cin >> a;
    while (b < a)
    {
        c++;
        b = b * 2;
    }
    std::cout << c;
}