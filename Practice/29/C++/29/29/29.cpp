#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl; 
using std::vector;
using std::setw;
using std::string;

struct Student
{
    std::string name;
    int group;
    std::map<std::string, int> exams;
};

bool operator > (Student one, Student two)
{
    return one.name > two.name;
}

std::ostream& operator<<(std::ostream& push, vector<Student> Loosers)
{
    push << "+--------------+-------+------+------+------+------+" << endl
        << "| Name         | Group | Math | Phys | Hist | Prog |"  << endl
        << "+--------------+-------+------+------+------+------+"  << endl;
    for (auto student : Loosers)
    {
        push << "| " << student.name << setw(15 - student.name.length())
            << "| " << student.group << setw(7)
            << "| " << student.exams["mathematics"] << setw(6)
            << "| " << student.exams["physics"] << setw(6)
            << "| " << student.exams["history"] << setw(6)
            << "| " << student.exams["programming"] << setw(5)
            << "|" << endl
            << "+--------------+-------+------+------+------+------+" << endl;
    }

    return push;
}

std::ostream& operator<<(std::ostream& push, Student looser)
{
    push << "+--------------+-------+------+------+------+------+" << endl
        << "| Name         | Group | Math | Phys | Hist | Prog |"  << endl
        << "+--------------+-------+------+------+------+------+"  << endl
        << "| " << looser.name << setw(15 - looser.name.length())
        << "| " << looser.group << setw(7)
        << "| " << looser.exams["mathematics"] << setw(6)
        << "| " << looser.exams["physics"] << setw(6)
        << "| " << looser.exams["history"] << setw(6)
        << "| " << looser.exams["programming"] << setw(5)
        << "|" << endl
        << "+--------------+-------+------+------+------+------+"  << endl;

    return push;
}

template <class T>
std::vector<T> BozoSort(vector<T> a)
{
    bool IfSorted = false;
    int n = a.size();

    while (IfSorted == 0)
    {
        std::swap(a[rand() % n], a[rand() % n]);

        IfSorted = true;

        for (int i = 1; i < n; i++)
        {
            if (a[i - 1.0] > a[i])
            {
                IfSorted = false;
                break;
            }
        }
    }

    return a;
}

int main()
{
    std::srand(time(0));
    vector<Student> Students, Loosers;
    Students =
    {
    { "Chahmarov O",  1, { {"mathematics", 5}, {"physics", 3}, {"history", 5}, {"programming", 5} } },
    { "Krasavec P",   1, { {"mathematics", 4}, {"physics", 4}, {"history", 5}, {"programming", 3} } },
    { "Nekrasavec E", 1, { {"mathematics", 2}, {"physics", 2}, {"history", 2}, {"programming", 2} } },
    { "Pushkin J",    1, { {"mathematics", 5}, {"physics", 2}, {"history", 3}, {"programming", 4} } },
    { "Gopnik G",     2, { {"mathematics", 3}, {"physics", 4}, {"history", 2}, {"programming", 3} } },
    { "Tolstoy L",    3, { {"mathematics", 4}, {"physics", 3}, {"history", 3}, {"programming", 4} } },
    { "Mashina F",    4, { {"mathematics", 2}, {"physics", 5}, {"history", 2}, {"programming", 3} } },
    { "Lobok v",      5, { {"mathematics", 3}, {"physics", 5}, {"history", 5}, {"programming", 5} } },
    { "Kirigaya K",   6, { {"mathematics", 4}, {"physics", 3}, {"history", 5}, {"programming", 3} } },
    { "Mochalka K",   7, { {"mathematics", 5}, {"physics", 5}, {"history", 3}, {"programming", 5} } }
    };

    int two = 0;

    for (auto student : Students)
    {
        for (auto mark : student.exams)
        {
            if (mark.second == 2)
            {
                two++;
                Loosers.push_back(student);
                break;
            }
        }
    }

    if (two == 0)
    {
        cout << "Not found";
    }
    else if (two == 1)
    {
        cout << Loosers[0] << endl
            << "Expulsion\n" << endl
            << Loosers[0];
    }
    else
    {
        cout << BozoSort(Loosers) << endl
            << "Expulsion\n" << endl
            << Loosers[rand() % Loosers.size()];
    }
}