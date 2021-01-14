#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

enum ItemType 
{
    COIN,
    RUNE,
    WEAPON,
    ARMOR
};

struct Coin 
{
    int count;
};

enum Element 
{
    FIRE,
    WATER,
    EARTH,
    AIR
};

struct Rune 
{
    int level;
    Element element;
};

struct Weapon 
{
    int damage;
    int critical;
    int durability;
};

struct Armor 
{
    int guard;
    int durability;
};

struct Item 
{
    ItemType type;
    union {
        Coin coin;
        Rune rune;
        Weapon weapon;
        Armor armor;
    } item;
};

Item randomItem(int num)
{
    switch (num)
    {
    case 1:
        return Item{
           RUNE, {.rune = { 10, FIRE }}
        };
        break;
    case 2:
        return Item{
           RUNE, {.rune = { 10, EARTH }}
        };
        break;
    case 3:
        return Item{
           RUNE, {.rune = { 10, WATER }}
        };
        break;
    case 4:
        return Item{
           RUNE, {.rune = { 10, AIR }}
        };
        break;
    case 5:
        return Item{
           RUNE, {.rune = { 5, FIRE }}
        };
        break;
    case 6:
        return Item{
           RUNE, {.rune = { 5, EARTH }}
        };
        break;
    case 7:
        return Item{
           RUNE, {.rune = { 5, WATER }}
        };
        break;
    case 8:
        return Item{
           RUNE, {.rune = { 5, AIR }}
        };
        break;
    case 9:
        return Item{
           WEAPON, {.weapon = { 100, 0, 100 }}
        };
        break;
    case 10:
        return Item{
           WEAPON, {.weapon = { 75, 50, 100 }}
        };
        break;
    case 11:
        return Item{
           ARMOR, {.armor = { 50, 100 }}
        };
        break;
    case 12:
        return Item{
           RUNE, {.rune = { 1, FIRE }}
        };
        break;
    case 13:
        return Item{
           RUNE, {.rune = { 1, EARTH }}
        };
        break;
    case 14:
        return Item{
           RUNE, {.rune = { 1, WATER }}
        };
        break;
    case 15:
        return Item{
           RUNE, {.rune = { 1, AIR }}
        };
        break;
    case 16:
        return Item{
           COIN, {.coin = { 1000 }}
        };
        break;
    default:
        break;
    }
}

std::ostream& operator << (std::ostream& out, Item item)
{
    std::string FullItemName;
    switch (item.type)
    {
    case COIN:
        FullItemName = "1000 gold";
        break;
    case RUNE:
        FullItemName = "Rune of ";
        switch (item.item.rune.element)
        {
        case FIRE:
            FullItemName += "fire";
            break;
        case EARTH:
            FullItemName += "earth";
            break;
        case WATER:
            FullItemName += "water";
            break;
        case AIR:
            FullItemName += "air";
            break;
        }
        FullItemName += " " + std::to_string(item.item.rune.level) + " lvl";
        break;
    case WEAPON:
        if (item.item.weapon.critical == 0)
        {
            FullItemName = "Weapon God Killer";
        }
        else if (item.item.weapon.critical == 50)
        {
            FullItemName = "Weapon Demon Slayer";
        }
        break;
    case ARMOR:
        FullItemName = "Bronezhiletka";
        break;
    }

    return out << FullItemName;
}

using LootBox = std::vector<Item>;
using std::endl;

std::ostream& operator << (std::ostream& out, LootBox Box)
{
    return out << Box[0] << endl << Box[1] << endl << Box[2] << endl;
}

std::vector<double> chances{ 0.06, 0.07, 0.13, 0.14, 0.6, 0.7, 1.3, 1.4, 1.4, 1.4, 2.8, 6.0, 7.0, 13.0, 14.0, 50.0 };

LootBox generateLootBox()
{
    LootBox Box;
    srand(time(0));

    for (int i = 0; i < 3; ++i)
    {
        double random = (rand() % 10000) / 100;
        double sum = 0;
        short num = 0;

        for (auto chance : chances)
        {
            ++num;
            if (sum <= random and random < sum + chance)
            {
                Item item = randomItem(num);
                Box.push_back(item);
                break;
            }

            sum += chance;
        }
    }

    return Box;
}

using std::cin;
using std::cout;

int main()
{
    setlocale(LC_ALL, "Russ");
    while (true)
    {
        std::string otvet;
        cout << "Открыть лутбокс? Yes/No" << std::endl;
        cin >> otvet;
        if (otvet == "Y" or otvet == "Yes" or otvet == "y" or otvet == "yes")
        {
            cout << generateLootBox();
        }
        else if (otvet == "N" or otvet == "No" or otvet == "n" or otvet == "no")
        {
            break;
        }
        else
        {
            continue;
        }
    }
}