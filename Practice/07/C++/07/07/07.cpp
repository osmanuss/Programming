#include <iostream>
#include <math.h>

int main()
{
    double a, b, c, s, p, a1, b1, c1, a2, b2, c2;
    int x;
    std::cin >> x;
    if (x == 1)
    {
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        p = ((a + b + c) / 2);
        s = sqrt(p*(p - a) * (p - b) * (p - c));
        std::cout << "S = " << s;
    }
    else
        if (x == 2)
        {
            std::cin >> a1 >> a2;
            std::cin >> b1 >> b2;
            std::cin >> c1 >> c2;
            a = sqrt((a1 - b1) * (a1 - b1) + (a2 - b2) * (a2 - b2));
            b = sqrt((c1 - b1) * (c1 - b1) + (c2 - b2) * (c2 - b2));
            c = sqrt((c1 - a1) * (c1 - a1) + (c2 - a2) * (c2 - a2));
            p = (a + b + c) / 2;
            s = sqrt(p*(p - a) * (p - b) * (p - c));
            std::cout << "S = " << s;
        }
        else
            std::cout << "Ошибочный ввод";
}