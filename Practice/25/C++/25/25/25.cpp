#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

std::vector<int> bozoSort(std::vector<int> arr, bool bl = 1)
{
	bool check = 1;
	while (check)
	{
		int a = rand() * arr.size() / RAND_MAX;
		int b = rand() * arr.size() / RAND_MAX;
		int tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
		if (bl)
		{
			bool tmpBool = 1;
			for (auto i = arr.begin(); i != arr.end() - 1; i++)
				if (*i > * (i + 1))
				{
					tmpBool = 0;
					break;
				}
			check = !tmpBool;
		}
		else
		{
			bool tmpBool = 1;
			for (auto i = arr.begin(); i != arr.end() - 1; i++)
				if (*i < *(i + 1))
				{
					tmpBool = 0;
					break;
				}
			check = !tmpBool;
		}
	}
	return arr;
}

std::vector <std::vector<int>> bozoSort(std::vector<std::vector<int>> arr, bool bl = 1)
{
	const int m = arr.size();
	const int n = arr[0].size();
	bool check = 1;
	while (check)
	{
		int rand_1_1 = rand() * n / RAND_MAX;
		int rand_1_2 = rand() * m / RAND_MAX;
		int rand_2_1 = rand() * n / RAND_MAX;
		int rand_2_2 = rand() * m / RAND_MAX;
		int tmp = arr[rand_1_2][rand_1_1];
		arr[rand_1_2][rand_1_1] = arr[rand_2_2][rand_2_1];
		arr[rand_2_2][rand_2_1] = tmp;

		if (bl)
		{
			bool tmpBool = 1;
			int previousNumber = arr[0][0];
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
				{
					if (previousNumber > arr[i][j])
					{
						tmpBool = 0;
					}
					previousNumber = arr[i][j];
				}
			check = !tmpBool;
		}
		else
		{
			bool tmpBool = 1;
			int previousNumber = arr[0][0];
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
				{
					if (previousNumber < arr[i][j])
					{
						tmpBool = 0;
					}
					previousNumber = arr[i][j];
				}
			check = !tmpBool;
		}
	}
	return arr;
}

std::vector<int> bozoSort(int a, int b, int c, bool bl = 1)
{
	std::vector<int> arr;
	arr.push_back(a);
	arr.push_back(b);
	arr.push_back(c);
	return bozoSort(arr, bl);
}

void printVector(std::vector<int> vec)
{
	for (auto i = vec.begin(); i != vec.end(); i++)
		std::cout << *i << ' ';
	std::cout << '\n';
}

void printVector(std::vector<std::vector<int>> vec)
{
	for (int i = 0; i < vec.size(); i++)
		for (int j = 0; j < vec[i].size(); j++)
			std::cout << vec[i][j] << ' ';
	std::cout << '\n';
}

int main()
{
	srand(time(NULL));
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		std::cin >> arr[i];
	std::vector<int> arr_1(n);
	for (int i = 0; i < n; i++) {
		arr_1[i] = arr[i];
	}
	auto arr_1_1 = bozoSort(arr_1);
	auto arr_1_2 = bozoSort(arr_1, 0);
	printVector(arr_1_1);
	printVector(arr_1_2);
	int m = sqrt(n);
	std::vector<std::vector<int>> arr_2(m, std::vector<int>(m));
	int k = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			arr_2[i][j] = arr[k++];
	auto arr_2_1 = bozoSort(arr_2);
	auto arr_2_2 = bozoSort(arr_2, 0);
	printVector(arr_2_1);
	printVector(arr_2_2);
	int a = arr[0];
	int b = arr[1];
	int c = arr[2];
	auto arr_3_1 = bozoSort(a, b, c);
	auto arr_3_2 = bozoSort(a, b, c, 0);
	printVector(arr_3_1);
	printVector(arr_3_2);
	delete[] arr;
	return 0;
}