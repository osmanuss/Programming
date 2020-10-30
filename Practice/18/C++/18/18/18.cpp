#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите слово." << std::endl;
    std::string pas;
    std::getline(std::cin, pas);
    const std::string words[] = { "hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen" };
    int chars[26] = {};
    const int x = 'a';
    for (const std::string& word : words)
    {
        for (const char& chr : word)
        {
            ++chars[chr - x];
        }
    }
    long double chance = 1;
    long double total = 0;
    for (const int& item : chars)
    {
        total += item;
    }
    for (const char& chr : pas)
    {
        chance *= chars[chr - x] / total;
        if (chance < LDBL_EPSILON) break;
    }
    std::cout.precision(16);
    std::cout << chance << std::endl;
}