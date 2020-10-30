#include <iostream>
#include <string>
#include <vector>
#include <cmath>

double pow(int a, int b)
{
	int var = 1;
	int i = 0;

	while (i++ < b)
		var *= a;

	return var;
}

int main()
{
	const int n = 6;
	std::string familiarWords[n] = { "hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen" };

	std::vector<char> familiarLetters;

	bool exist = 1;

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < familiarWords[i].length(); j++) 
		{
			for (auto k = familiarLetters.begin(); k < familiarLetters.end(); k++)
				if (*k == familiarWords[i][j])
					exist = 0;

			if (exist)
				familiarLetters.push_back(familiarWords[i][j]);

			exist = 1;
		}

	std::string stopWord;
	std::cin >> stopWord;

	std::vector<bool> arr(stopWord.length());

	for (int i = 0; i < stopWord.length(); i++)
		arr[i] = 0;

	for (int i = 0; i < stopWord.length(); i++)
		for (auto k = familiarLetters.begin(); k < familiarLetters.end(); k++)
			if (*k == stopWord[i])
			{
				arr[i] = 1;
				break;
			}

	exist = 1;
	for (int i = 0; i < stopWord.length(); i++)
		exist *= arr[i];

	if (exist)
		std::cout << pow(double(1) / familiarLetters.size(), stopWord.length());
	else
		std::cout << 0;

	return 0;
}