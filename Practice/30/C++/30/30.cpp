#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <cctype>

enum class ItemType
{
	COIN,
	RUNE,
	WEAPON,
	ARMOR
};

struct Coin
{
	size_t count;
};

enum class Element
{
	FIRE,
	WATER,
	EARTH,
	AIR
};

struct Rune
{
	Element element;
	size_t level;
};

struct Weapon
{
	size_t damage;
	size_t critical;
	size_t durability;
};

struct Armor
{
	size_t guard;
	size_t durability;
};

union Union
{
	Coin coin;
	Rune rune;
	Weapon weapon;
	Armor armor;

	Union(const Coin& coin)
	{
		this->coin = coin;
	}

	Union(const Rune& rune)
	{
		this->rune = rune;
	}

	Union(const Weapon& weapon)
	{
		this->weapon = weapon;
	}

	Union(const Armor& armor)
	{
		this->armor = armor;
	}
};

struct Item
{
	ItemType type;

	Union value;

	static Item GetCoin(const unsigned int count)
	{
		return {
			Item{
				ItemType::COIN,
				Union{Coin{count}}
			}
		};
	}

	static Item GetRune(const Element element, const size_t level)
	{
		return
		{
			Item{
				ItemType::RUNE,
				Union{Rune{element, level}}
			}
		};
	}

	static Item GetWeapon(const unsigned int damage, const size_t critical, const size_t durability)
	{
		return {
			Item{
				ItemType::WEAPON,
				Union{Weapon{damage, critical, durability}}
			}
		};
	}

	static Item GetArmor(const unsigned int guard, const size_t durability)
	{
		return {
			Item{
				ItemType::ARMOR,
				Union{Armor{guard, durability}}
			}
		};
	}

	Item& operator++()
	{
		return *this;
	}
};

std::string write(Rune& rune)
{
	std::string result;

	switch (rune.element)
	{
	case Element::FIRE:
		return "fire";
	case Element::WATER:
		return "water";
	case Element::EARTH:
		return "earth";
	case Element::AIR:
		return "air";
	}
}

std::ostream& operator <<(std::ostream& out, const Item& item)
{
	const ItemType type = item.type;

	if (type == ItemType::COIN)
	{
		out << item.value.coin.count << " gold" << std::endl;
	}
	if (type == ItemType::RUNE)
	{
		Rune rune = item.value.rune;
		out << "Rune of " << write(rune) << " " << rune.level << " lvl" << std::endl;
	}
	if (type == ItemType::WEAPON)
	{
		Weapon weapon = item.value.weapon;
		if (weapon.damage == 100)
		{
			out << "God Killer" << std::endl;
		}
		else
		{
			out << "Demon Slayer" << std::endl;
		}
	}
	if (type == ItemType::ARMOR)
	{
		const Armor armor = item.value.armor;
		out << "bronezhiletka" << std::endl;
	}
	return out;
}

using LootBox = std::vector<Item>;

std::ostream& operator <<(std::ostream& out, const LootBox& box)
{
	for (const Item& item : box)
	{
		out << item;
	}

	return out << std::flush;
}

LootBox& operator<<(LootBox& box, Item& item)
{
	box.push_back(item);
	return box;
}

std::vector<std::pair<Item, double>> treasure
{
	{Item::GetCoin(1000), 50.0},
	{Item::GetRune(Element::FIRE, 1), 6.0},
	{Item::GetRune(Element::WATER, 1), 13.0},
	{Item::GetRune(Element::EARTH, 1), 7.0},
	{Item::GetRune(Element::AIR, 1), 14.0},
	{Item::GetRune(Element::FIRE, 5), 0.6},
	{Item::GetRune(Element::WATER, 5), 1.3},
	{Item::GetRune(Element::EARTH, 5), 0.7},
	{Item::GetRune(Element::AIR, 5), 1.4},
	{Item::GetRune(Element::FIRE, 5), 0.06},
	{Item::GetRune(Element::WATER, 5), 0.13},
	{Item::GetRune(Element::EARTH, 5), 0.07},
	{Item::GetRune(Element::AIR, 5), 0.14},
	{Item::GetWeapon(100, 0, 100), 1.4},
	{Item::GetWeapon(75, 50, 100), 1.4},
	{Item::GetArmor(50, 100), 2.8},
};

LootBox generateLootBox()
{
	LootBox box;
	std::srand(std::time(nullptr));

	for (int i = 0; i < 3; ++i)
	{
		const double random = static_cast<double>(rand() % 10000) / 100;
		double sum = 0;

		for (const auto& item : treasure)
		{
			if (sum <= random && random < sum + item.second)
			{
				box.push_back(item.first);
				break;
			}

			sum += item.second;
		}
	}

	return box;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	while (true)
	{
		std::string answer;
		std::cout << "Открыть лутбокс? Yes/No" << std::endl;
		std::cin >> answer;

		if (answer == "y" or answer == "Y" or answer == "yes" or answer == "Yes")
		{
			std::cout << generateLootBox();
		}
		else if (answer == "n" or answer == "N" or answer == "no" or answer == "No")
		{
			break;
		}
	}
};