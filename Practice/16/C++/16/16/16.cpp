#include <iostream>
#include <sstream>
#include <string>
#include <regex>

const std::regex regex = std::regex("^a(?:(?:[a-z][0-9]{2})|(?:[0-9][a-z][0-9])|(?:[0-9]{2}[a-z]))55661$");
bool isMatch(const std::string& str)
{
    return std::regex_match(str, regex);
}

bool getInput(int& x)
{
    std::cin >> x;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return false;
    }
    std::cin.ignore(32767, '\n');
    return true;
}

void tryRead(int& value)
{
    while (!getInput(value))
    {
        std::cout << "Неверный ввод. Повторите попытку." << std::endl;
    }
}

size_t split(const std::string& str, std::vector<std::string>& strings, const char delimiter = ' ')
{
    size_t pos = str.find(delimiter);
    size_t start = 0;
    strings.clear();
    while (pos != std::string::npos) {
        strings.push_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find(delimiter, start);
    }
    strings.push_back(str.substr(start, std::min(pos, str.size()) - start + 1));
    return strings.size();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    do
    {
        tryRead(n);
        if (n < 1)
        {
            std::cout << "Число меньше 1. Повторите ввод." << std::endl;
            continue;
        }
        break;
    } while (true);
    std::vector<std::string> bilets;
    std::string input;
    std::getline(std::cin, input);
    split(input, bilets);
    std::stringstream stream;
    for (int i = 0; i < bilets.size(); i++)
    {
        if (isMatch(bilets[i]))
        {
            stream << bilets[i];

            if (i < bilets.size() - 1)
            {
                stream << " ";
            }
        }
    }
    std::string result = stream.str();
    if (result.empty())
    {
        result = "-1";
    }
    std::cout << result << std::endl;
}