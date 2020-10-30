#include <iostream>
#include <vector>

struct Ruletka
{
	int num;
	int color;
	int dorpRate;
};

int main()
{
	const int n = 37;

	Ruletka arr[n];
	memset(arr, 0, sizeof(arr));

	for (int i = 1; i < n; i++)
		arr[i].num = i;

	for (int i = 1; i < 11; i++)
		arr[i].color = i % 2;

	arr[11].color = 0;

	for (int i = 12; i < 19; i++)
		arr[i].color = (i + 1) % 2;

	for (int i = 19; i < 29; i++)
		arr[i].color = i % 2;

	arr[29].color = 0;

	for (int i = 30; i < n; i++)
		arr[i].color = (i + 1) % 2;

	std::vector<int> drop_rate_nums;
	for (int i = 0; i < n; i++)
		drop_rate_nums.push_back(i);

	std::pair<int, int> drop_rate_b_r;
	drop_rate_b_r.first = 0;
	drop_rate_b_r.second = 0;

	int most_drops = 0;

	int k = 3;
	int cin;

	while (true)
	{
		for (int j = 0; j < k; j++)
		{
			std::cin >> cin;
			if (cin < 0)
				return 0;
			if (cin > 36)
				continue;

			arr[cin].dorpRate++;

			for (int i = 0; i < n; i++)
				if (arr[i].dorpRate > most_drops)
					most_drops = arr[i].dorpRate;

			for (int i = 0; i < n; i++)
				if (arr[i].dorpRate == most_drops)
					std::cout << arr[i].num << ' ';
			std::cout << '\n';

			for (auto i = drop_rate_nums.begin(); i < drop_rate_nums.end(); i++)
				if (*i == cin)
				{
					drop_rate_nums.erase(i);
					break;
				}

			for (auto i = drop_rate_nums.begin(); i < drop_rate_nums.end(); i++)
				std::cout << *i << ' ';
			std::cout << '\n';

			arr[cin].color == 0 ? drop_rate_b_r.first++ : drop_rate_b_r.second++;

			std::cout << drop_rate_b_r.second << ' ' << drop_rate_b_r.first << "\n\n";
		}

		for (int i = 0; i < n; i++)
			arr[i].dorpRate = 0;

		drop_rate_nums.clear();
		for (int i = 0; i < n; i++)
			drop_rate_nums.push_back(i);

		drop_rate_b_r.first = 0;
		drop_rate_b_r.second = 0;
		most_drops = 0;
	}

	return 0;
}