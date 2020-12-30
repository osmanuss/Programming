#include <iostream>
#include <map>
#include <iomanip>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::vector;

struct Student//бедные
{
    std::string name;
    short group;
    std::map<std::string, short> exams;
};

bool operator > (Student first, Student second)
{
    return first.name > second.name;
}

std::ostream& operator<<(std::ostream& out, vector<Student> BadLeanners)
{
    out << "+--------------+-------+------+------+------+------+" << endl
        << "| Name         | Group | Math | Phys | Hist | Prog |" << endl
        << "+--------------+-------+------+------+------+------+" << endl;
    for (auto student : BadLeanners)
    {
        out << "| " << student.name << setw(15 - student.name.length())
            << "| " << student.group << setw(7)
            << "| " << student.exams["math"] << setw(6)
            << "| " << student.exams["phys"] << setw(6)
            << "| " << student.exams["hist"] << setw(6)
            << "| " << student.exams["prog"] << setw(5)
            << "|" << endl
            << "+--------------+-------+------+------+------+------+" << endl;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, Student BadLeanner)
{
    out << "+--------------+-------+------+------+------+------+" << endl
        << "| Name         | Group | Math | Phys | Hist | Prog |" << endl
        << "+--------------+-------+------+------+------+------+" << endl
        << "| " << BadLeanner.name << setw(15 - BadLeanner.name.length())
        << "| " << BadLeanner.group << setw(7)
        << "| " << BadLeanner.exams["math"] << setw(6)
        << "| " << BadLeanner.exams["phys"] << setw(6)
        << "| " << BadLeanner.exams["hist"] << setw(6)
        << "| " << BadLeanner.exams["prog"] << setw(5)
        << "|" << endl
        << "+--------------+-------+------+------+------+------+" << endl;

    return out;
}

template <class T>
std::vector<T> BozoSort(vector<T> arr)
{
    bool sorted = false;
    int n = arr.size();

    while (!sorted)
    {
        std::swap(arr[rand() % n], arr[rand() % n]);

        sorted = true;

        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                sorted = false;
                break;
            }
        }
    }

    return arr;
}

int main()
{
    std::srand(time(0));
    vector<Student> StudentsList, BadLearners;
    StudentsList = {
    { "Kirito",  1, { {"math", 5}, {"phys", 5}, {"hist", 5}, {"prog", 5} } },
    { "Asuna",   1, { {"math", 5}, {"phys", 5}, {"hist", 5}, {"prog", 5} } },
    { "Eugeo",   1, { {"math", 5}, {"phys", 5}, {"hist", 5}, {"prog", 5} } },
    { "Sinon",   1, { {"math", 2}, {"phys", 2}, {"hist", 2}, {"prog", 2} } },
    { "Klein",   2, { {"math", 3}, {"phys", 4}, {"hist", 2}, {"prog", 3} } },
    { "Deathgun",3, { {"math", 5}, {"phys", 3}, {"hist", 3}, {"prog", 4} } },
    { "Vector",  4, { {"math", 2}, {"phys", 3}, {"hist", 2}, {"prog", 3} } },
    { "Kayaba",  5, { {"math", 3}, {"phys", 4}, {"hist", 5}, {"prog", 5} } },
    { "Yui",     6, { {"math", 5}, {"phys", 5}, {"hist", 5}, {"prog", 3} } },
    { "Obama",   7, { {"math", 5}, {"phys", 3}, {"hist", 3}, {"prog", 4} } } };//Черный всегда должен быть

    short lohi = 0;

    for (auto student : StudentsList)
    {
        for (auto mark : student.exams)
        {
            if (mark.second == 2)
            {
                lohi++;
                BadLearners.push_back(student);
                break;
            }
        }
    }

    if (lohi == 0)
    {
        cout << "Not found";//Повезло))
    }
    else if (lohi == 1)//Слабое звено
    {
        cout << BadLearners[0] << endl
            << "Expulsion\n" << endl
            << BadLearners[0];
    }
    else
    {
        cout << BozoSort(BadLearners) << endl//Ну тут бан
            << "Expulsion\n" << endl
            << BadLearners[rand() % BadLearners.size()];
    }
}