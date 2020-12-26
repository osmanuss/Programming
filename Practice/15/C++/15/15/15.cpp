#include <iostream>
#include <random>
#include <ctime>

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int a, b, x, z;
    x = 1;
    z = 1;
    setlocale(LC_ALL, "Russian");
    std::cout << "Здраствуйте\n";
    while (x == 1)
    {
        std::cout << "Сейчас я загадаю число от нуля до ста, и вы попробуете угадать его. Ну что ж, приступаем!" << std::endl;
        b = getRandomNumber(1,100);
        std::cin >> a;
        while (z < 5)
        {
            z = z + 1;
            if (a > b)
                std::cout << "Загаданное число меньше" << std::endl;
            else
                if (a < b)
                    std::cout << "Загаданное число больше" << std::endl;
                else
                    break;
            std::cin >> a;
        }
        if (a == b)
            std::cout << "Поздравляю! Вы угадали" << std::endl;
        else
            std::cout << "Вы проиграли. Было загадано: " << b<<std::endl;
        std::cout << "Хотите начать сначала?";
        std::cin >> x;
    }
}