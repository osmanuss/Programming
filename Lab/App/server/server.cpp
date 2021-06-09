#include <iostream>
#include <string>
#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>

using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
using namespace httplib;
using json = nlohmann::json;
using std::endl;
json config;

ofstream logger("log.txt");


const int x = 6;
const int y = 7;
int ary[x][y] =
{
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}
};
int end = 0;
int step = 1;
int a;
bool ending = 0;
json RawCache;



void rascheti(int a)
{
    if (step == 1)
    {
        std::cout << "\nХодит красный\n";
        if (a > 7)
            return;
    }
    else
    {
        std::cout << "\nХодит желтый\n";
        if (a < 8)
            return;
        else
            a = a - 7;
    }
    a = a - 1;

    if ((a > 6) or (a < 0))
        return;

    for (int i = 1; i < 7; i++)                     // Падение фишки
    {
        if (ary[6 - i][a] == 0)
        {
            ary[6 - i][a] = step;
            break;
        }
        if (i == 6)
            return;
    }


    for (int i = 0; i < 6; i++)                     // Вычисление победителя по горизонтали
    {
        for (int j = 0; j < 4; j++)
        {
            if ((ary[i][j] == step) and (ary[i][j + 1] == step) and (ary[i][j + 2] == step) and (ary[i][j + 3] == step))
                ending = 1;
        }
    }

    for (int i = 0; i < 4; i++)                     // Вычисление победителя по вертикали
    {
        for (int j = 0; j < 7; j++)
        {
            if ((ary[i][j] == step) and (ary[i + 1][j] == step) and (ary[i + 2][j] == step) and (ary[i + 3][j] == step))
                ending = 1;
        }
    }

    for (int i = 0; i < 4; i++)                     // Вычисление победителя по диагонали вниз
    {
        for (int j = 0; j < 4; j++)
        {
            if ((ary[i][j] == step) and (ary[i + 1][j + 1] == step) and (ary[i + 2][j + 2] == step) and (ary[i + 3][j + 3] == step))
                ending = 1;
        }
    }

    for (int i = 3; i < 6; i++)                     // Вычисление победителя по диагонали вверх
    {
        for (int j = 0; j < 4; j++)
        {
            if ((ary[i][j] == step) and (ary[i - 1][j + 1] == step) and (ary[i - 2][j + 2] == step) and (ary[i - 3][j + 3] == step))
                ending = 1;
        }
    }

    if (ending == 1)                                  // Объявление победителя
    {
        if (step == 1)
        {
            std::cout << "\nВыиграл красный\n";
            step = 3;
            end = 1;
        }
        else
        {
            std::cout << "\nВыиграл желтый\n";
            end = 1;
            step = 4;
        }
    }

    for (int i = 0; i < 6; i++)         //Вывод массива
    {
        for (int j = 0; j < 7; j++)
        {
            std::cout << ary[i][j] << "  ";
        }
        std::cout << std::endl;
    }

    if (step == 1)             // Переход хода
    {
        step = 2;
    }
    else
    {
        if (step == 2)
        {
            step = 1;
        }
    }



    RawCache["step"] = step - 1;
    RawCache["array"] = ary;
    ofstream wc("example.json");
    cout << "Generating cache..." << endl;
    wc << std::setw(2) << RawCache << std::endl;
}

void gen_red(const Request& req, Response& res)
{
    string widget;
    ifstream rw("../site/red.html");
    if (rw.is_open()) // если открылся
    {
        getline(rw, widget, '\0'); // читаем его содежимое
    }
    else // в противном случае говорим что шаблон не открылся
        cout << "Can`t open template";
    res.set_content(widget, "text/html");
}

void gen_yellow(const Request& req, Response& res)
{
    string widget;
    ifstream rw("../site/yellow.html");
    if (rw.is_open()) // если открылся
    {
        getline(rw, widget, '\0'); // читаем его содежимое
    }
    else // в противном случае говорим что шаблон не открылся
        cout << "Can`t open template";
    res.set_content(widget, "text/html");
}

void gen_sait(const Request& req, Response& res)
{
    string widget;
    ifstream rw("../site/sait.html");
    if (rw.is_open()) // если открылся
    {
        getline(rw, widget, '\0'); // читаем его содежимое
    }
    else // в противном случае говорим что шаблон не открылся
        cout << "Can`t open template";
    res.set_content(widget, "text/html");
}

void gen_redpost(const Request& req, Response& res)
{

    string widget;
    ifstream rw("../site/red.html");
    if (rw.is_open()) // если открылся
    {
        getline(rw, widget, '\0'); // читаем его содежимое
    }
    else // в противном случае говорим что шаблон не открылся
        cout << "Can`t open template";
    string a = req.body.c_str();
    a.erase(a.find("="), 1);
    cout << a << std::endl;
    int i = std::stoi(a);
    if (end == 0)
        rascheti(i);


    res.set_content(widget, "text/html");
}

void gen_yellowpost(const Request& req, Response& res)
{
    string widget;
    ifstream rw("../site/yellow.html");
    if (rw.is_open()) // если открылся
    {
        getline(rw, widget, '\0'); // читаем его содежимое
    }
    else // в противном случае говорим что шаблон не открылся
        cout << "Can`t open template";
    string a = req.body.c_str();
    a.erase(a.find("="), 1);
    cout << a << std::endl;
    int i = std::stoi(a);
    if (end == 0)
        rascheti(i);

    res.set_content(widget, "text/html");
}

void gen_response(const Request& req, Response& res)
{
    std::fstream f_json("example.json");
    json finish;
    finish = json::parse(f_json);
    res.set_content(finish.dump(), "text/json");
}

void new_game(const Request& req, Response& res)
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            ary[i][j] = 0;
    step = 1;
    end = 0;
    ending = 0;
    std::cout << "replay";


    RawCache["step"] = step - 1;
    RawCache["array"] = ary;
    ofstream wc("example.json");
    cout << "Generating cache..." << endl;
    wc << std::setw(2) << RawCache << std::endl;
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Игра началась";

    RawCache["step"] = 0;
    RawCache["array"] = ary;
    ofstream wc("example.json");
    cout << "\nGenerating cache...\n" << endl;
    wc << std::setw(2) << RawCache << std::endl;

    Server svr;                            // Создаём сервер (пока-что не запущен)
    svr.Get("/red", gen_red);
    svr.Get("/yellow", gen_yellow);
    svr.Get("/sait", gen_sait);
    svr.Get("/", gen_response);
    svr.Get("/new", new_game);
    svr.Post("/red", gen_redpost);
    svr.Post("/yellow", gen_yellowpost);
    std::cout << "Start server... OK\n";
    svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
}