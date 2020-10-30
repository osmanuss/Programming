#include <iostream>
#include <vector>
#include <string>

struct buhlo
{
	std::string drink{ "" };
	int price{ 0 };
	int v{ 0 };
	double benefit{ 0 };
	int counter{ 0 };
};

int main()
{
	int n, k, m; 
	std::cin >> n;
	m = n;
	std::cin >> k;
	std::vector<buhlo> arr(k);
	for (int i = 0; i < k; i++)
	{
		std::string name;
		std::cin >> name;
		arr[i].drink = name;
		int price;
		std::cin >> price;
		arr[i].price = price;
		int v;
		std::cin >> v;
		arr[i].v = v;
		arr[i].benefit = double(v) / price;
	}
	std::cout << '\n';
	for (int i = 0; i < k - 1; i++)
		for (int j = 0; j < k - i - 1; j++)
			if (arr[j].benefit < arr[j + 1].benefit)
			{
				auto temp1 = arr[j].benefit;
				arr[j].benefit = arr[j + 1].benefit;
				arr[j + 1].benefit = temp1;
				auto temp2 = arr[j].drink;
				arr[j].drink = arr[j + 1].drink;
				arr[j + 1].drink = temp2;
				auto temp3 = arr[j].v;
				arr[j].v = arr[j + 1].v;
				arr[j + 1].v = temp3;
				auto temp4 = arr[j].price;
				arr[j].price = arr[j + 1].price;
				arr[j + 1].price = temp4;
			}
	for (int i = 0; i < k; i++)
		while (n - arr[i].price > 0)
		{
			arr[i].counter++;
			n -= arr[i].price;
		}
	for (int i = 0; i < k; i++)
	{
		if (arr[i].counter)
		{
			std::cout << arr[i].drink << ' ' << arr[i].counter << '\n';
			std::cout << arr[i].v * arr[i].counter << '\n';
		}
	}
	if (m == n)
	{
		std::cout << "-1";
	}
	else
	{
		std::cout << n;
	}
	return 0;
}