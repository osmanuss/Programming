<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 1<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-201(1)<br>
Чахмаров Осман Рустемович<br>
направления подготовки 09.03.04 "Название направления подготовки"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

## Постановка задачи

Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса. В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С ++ и клиентское приложение на языке Python.

Серверное приложение (далее) Серверное предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность передачи данных в формате JSON и виде html виджета (для вставки виджета на страницу будет поддерживать данные iframe).

Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

## Цель работы

- Закрепление навыков работы с json
- Закрепление навыков работы с многофайловыми приложениями
- Получение базового представления о взаимодействии приложений в клиент-сервеном приложении
- Изучение структуры html запроса

## Выполнение работы

##### Подготовка перед созданием программы

1. ### Регистрируемся на сервисе openweathermap.org и получаем API-ключ.
<details>
  <summary> Мой API-ключ </summary>

  ``
  8ef4d6cf87e941cd535e7c370ad0a401
  ``
</details>

2. ### Составим запрос, соответствующий указанниям в тз (Составьте запрос на получение прогноза погоды для Симферополя с почасовым интервалом, в градусах Цельсия, на русском языке)
<details>
  <summary> Мой запрос </summary>

  ``
  http://api.openweathermap.org/data/2.5/onecall?lat=44&lon=34&units=metric&exclude=current,minutely,daily,alerts&lang=ru&appid=8ef4d6cf87e941cd535e7c370ad0a401
  ``
</details>

3. ### Составляем запрос на получение времени в Симферополе
<details>
<summary> Мой запрос </summary>

  ``
http://worldtimeapi.org/api/timezone/Europe/Simferopol
  ``
</details>

4. ### Сервер

Создаём серверное приложение. Сервер слушает запросы на 3000 порт localhost. При определенном запросе он выдает либо html-вид, либо обработанный json, который он получил с помощью openweathermap и обработал. Данные хранятся в кэше, который обновляется, при устаревании.

<details>

```c++
#include <iostream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>
using json = nlohmann::json;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using namespace httplib;
void gen_response(const Request& req, Response& res);
void gen_response_raw(const Request& req, Response& res);
json GetWeather()
{
    string req;
    req = "/data/2.5/onecall?lat=44&lon=34&units=metric&exclude=current,minutely,daily,alerts&lang=ru&appid=8ef4d6cf87e941cd535e7c370ad0a401";
    Client get_time("http://api.openweathermap.org");
    auto res = get_time.Get(req.c_str());
    if (res) {
        if (res->status == 200)
        {
            json result = res->body;
            return result;
        }
        else
        {
            cout << "Status code: " << res->status << endl;
        }
    }
    else
    {
        auto err = res.error();
        cout << "Error code: " << err << endl;
    }
}
string GetTime()
{
    Client get_time("http://worldtimeapi.org");
    auto res = get_time.Get("/api/timezone/Europe/Simferopol");
    if (res) {
        if (res->status == 200)
        {
            string result = res->body;
            return result;
        }
        else
        {
            cout << "Status code: " << res->status << endl;
        }
    }
    else
    {
        auto err = res.error();
        cout << "Error code: " << err << endl;
    }
}
bool is_empty_file(std::ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}
json CacheGenerator(ifstream& ReadCache)
{
    json RawCache;
    RawCache = GetWeather();
    ofstream wc("cache.json");
    cout << "Generating cache..." << endl;
    wc << std::setw(2) << RawCache << std::endl;
    return RawCache;
}
string StringRemoover(string FToRemoove, json cache, int curr_hour)
{
    string r1 = "{hourly[i].weather[0].description}";
    string r2 = "{hourly[i].weather[0].icon}";
    string r3 = "{hourly[i].temp}";
    double tempd = cache["hourly"][curr_hour]["temp"];
    string temps = std::to_string(int(round(tempd)));
    string desk = cache["hourly"][curr_hour]["weather"][0]["description"];
    string icon = cache["hourly"][curr_hour]["weather"][0]["icon"];
    FToRemoove.replace(FToRemoove.find(r1), r1.length(), desk);
    FToRemoove.replace(FToRemoove.find(r2), r2.length(), icon);
    FToRemoove.replace(FToRemoove.find(r3), r3.length(), temps);
    FToRemoove.replace(FToRemoove.find(r3), r3.length(), temps);
    return FToRemoove;
}
int WhatHour(json cache)
{
    int curr_hour = 100;
    long unixtime;
    json curr_time_full = json::parse(GetTime());
    unixtime = curr_time_full["unixtime"];
    for (int i = 0; i < 48; i++)
    {
        long w_unixtime = cache["hourly"][i]["dt"];
        if (unixtime < w_unixtime)
        {
            curr_hour = i;
            break;
        }
    }
    return curr_hour;
}
json CacheReader(ifstream& rc)
{
    json RawCache;
    bool not_exist_cache = !rc.is_open() or is_empty_file(rc);
    if (not_exist_cache)
    {
        RawCache = CacheGenerator(rc);
    }
    else
    {
        rc >> RawCache;
        cout << "Cache succesfully read" << endl;
    }
    return RawCache;
}
void gen_response_raw(const Request& req, Response& res)
{
    ifstream rc("cache.json");
    json RawCache = CacheReader(rc);
    string temp = RawCache;
    json cache = json::parse(temp);
    int curr_hour = WhatHour(cache);
    if (curr_hour == 100)
    {
        RawCache = CacheGenerator(rc);
        temp = RawCache;
        cache = json::parse(temp);
    }
    json WeatherData;
    double tempd = cache["hourly"][curr_hour]["temp"];
    int tempi = round(tempd);
    string desk = cache["hourly"][curr_hour]["weather"][0]["description"];
    WeatherData["temperature"] = tempi;
    WeatherData["description"] = desk;
    res.set_content(WeatherData.dump(), "text/json");
}
void gen_response(const Request& req, Response& res)
{
    ifstream rc("cache.json");
    json RawCache = CacheReader(rc);
    string temp = RawCache;
    json cache = json::parse(temp);
    int curr_hour = WhatHour(cache);
    if (curr_hour == 100)
    {
        RawCache = CacheGenerator(rc);
        temp = RawCache;
        cache = json::parse(temp);
    }
    string widget;
    ifstream rw("template.html");
    if (rw.is_open())
    {
        getline(rw, widget, '\0');
    }
    else
        cout << "Can`t open template";
    string output = StringRemoover(widget, cache, curr_hour);
    res.set_content(output, "text/html");
}
int main()
{
    Server svr;
    svr.Get("/", gen_response);
    svr.Get("/raw", gen_response_raw);
    cout << "Start server... OK\n";
    svr.listen("localhost", 3000);
}
```
</details>

5. ### Клиент
Создаём клиентское приложение, которое будет посылать запросы на наш локальный сервер при помощи "requests", обрабатывать json файл с помощью модуля "json" и отображать погоду на текущий момент при помощи "Tkinter". Приложение создается на python с использованием библиотеки tkinter.

<details>


```Python
from tkinter import *
import json
import requests
def WeatherReload(event=None):
    r = requests.get('http://localhost:3000/raw').content.decode("UTF8")
    weather = json.loads(r)
    description.config(text=str(weather["description"]))
    temperature.config(text=str(weather["temperature"]) + "°C")
root = Tk()
root.title("Погода")
root.bind("<Button-3>", WeatherReload)
root.geometry("185x220")
TopFrame = Frame(root, bg="#ffcd57")
MiddleFrame = Frame(root, bg="white")
BottomFrame = Frame(root, bg="#ffcd57", height=30)
TopFrame.pack(side=TOP, fill=X)
MiddleFrame.pack(expand=True, fill=BOTH)
BottomFrame.pack(side=BOTTOM, fill=X)
city = Label(TopFrame, font=("Franklin Gothic Medium", 12), text="Симферополь", bg="#ffcd57")
description = Label(TopFrame, font=("Georgia", 12), bg="#ffcd57")
temperature = Label(MiddleFrame, font=("Impact", 60), bg="white")
city.pack()
description.pack()
temperature.pack(expand=True)
WeatherReload()
root.mainloop()
```
</details>

6. ### Внешний вид HTML-виджета и python-приложения

Скриншот виджета:

! [] (./ image / app.png)
* рис. 1 html-виджет *

Скриншот клиента:

! [] (./ image / widget.png)
* рис. 2 клиентское приложение *

## Вывод

В процессе выполнения лабораторной работы я закрепил свои навыки работы с json и многофайловыми приложениями, получил представление об обратной стороне клиент-серверного приложения, закрепил свои знания о структуре http запроса.