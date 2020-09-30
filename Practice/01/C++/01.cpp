#include<iostream>
#include <Windows.h>
int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Результат выражения 2+2*2 = " << (2 + 2 * 2);
}
