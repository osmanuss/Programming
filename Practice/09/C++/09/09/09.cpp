#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    int h1, h2, m1, m2;
    char a;
    std::cin >> h1 >> a >> m1;
    std::cin >> h2 >> a >> m2;
    h1 = h1 * 60 + m1;
    h2 = h2 * 60 + m2;
    if (abs(h1 - h2) <= 15)
        std::cout << "Встреча состоится";
    else
        std::cout << "Встреча не состоится";
}