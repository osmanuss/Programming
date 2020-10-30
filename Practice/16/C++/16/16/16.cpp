#include <iostream>
int main() {
	setlocale(LC_ALL, "ru");
	int i, n, f;
	f = 0;
	std::cin >> n;
	std::string a{};
	for (i = 1; i <= n; i++)
	{
		std::cin >> a;
		if (a[0] == 'a' && a[4] == '5' && a[5] == '5' && a[6] == '6' && a[7] == '6' && a[8] == '1')
		{
			std::cout << a << ' ';
			f++;
		}
	}
	if (f == 0)
	{
		std::cout << "-1";
	}
	return 0;
}