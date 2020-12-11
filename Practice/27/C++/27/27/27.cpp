#include <iostream>

void top(int* arr)
{
	int n = 5;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (arr[j] < arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
}

int main()
{
	int n;
	std::cin >> n;
	int* arr = new int[5];
	for (int i = 0; i < 5; i++)
		arr[i] = -1;
	if (n <= 5)
		for (int i = 0; i < n; i++)
		{
			std::cin >> arr[i];
			top(arr);
			for (int j = 0; j < i + 1; j++)
				std::cout << arr[j] << ' ';
			std::cout << '\n';
		}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			std::cin >> arr[i];
			top(arr);

			for (int j = 0; j < i + 1; j++)
				std::cout << arr[j] << ' ';
			std::cout << '\n';
		}
		for (int i = 5; i < n; i++)
		{
			int cin;
			std::cin >> cin;
			bool isSorted = true;
			for (int j = 4; j >= 0; j--)
			{
				if (cin < arr[j])
				{
					arr[0] = cin;
					isSorted = false;
					break;
				}
			}
			if (!isSorted)
				top(arr);
			for (int j = 0; j < 5; j++)
				std::cout << arr[j] << ' ';
			std::cout << '\n';
		}
	}
	delete[] arr;
}