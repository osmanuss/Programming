<<<<<<< HEAD
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
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
=======
<p align = "center"> МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ <br>
Федеральное государственное автономное образовательное учреждение высшего образования <br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО" <br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ <br>
Кафедра компьютерной инженерии и моделирования </p>
<br>
<h3 align = "center"> Отчёт по лабораторной работе № X <br> по дисциплине "Программирование" </h3>
<br> <br>
<p> студента 1 курса группы ПИ-б-о-201 (2) <br>
Чахмаров Осман Рустемович <br>
направления подготовки 09.03.04 "Программная инженерия" </p>
<br> <br>
<таблица>
<tr> <td> Научный руководитель <br> старший преподаватель кафедры компьютерной инженерии и моделирования </td>
<td> (оценка) </td>
<td> Чабанов В.В. </td>
</tr>
</table>
<br> <br>
<p align = "center"> Симферополь, 2020 </p>
>>>>>>> cd59c3e8db2e5ff574d0704835ecbf115fcc6726
<hr>

## Постановка задачи

<<<<<<< HEAD
Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса. В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.

Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).
=======
Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса. В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С ++ и клиентское приложение на языке Python.

Серверное приложение (далее) Серверное предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность передачи данных в формате JSON и виде html виджета (для вставки виджета на страницу будет поддерживать данные iframe).
>>>>>>> cd59c3e8db2e5ff574d0704835ecbf115fcc6726

Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

## Цель работы

- Закрепление навыков работы с json
- Закрепление навыков работы с многофайловыми приложениями
<<<<<<< HEAD
- Получение базового представления о взаимодействии приложений посредством создания клиент-сервеного приложения
- Получение знаний о структуре html запроса

Каталоги:
[[Сервер]](./C++) [[Клиент]](./Python)

## Выполнение работы

1. Регистрируемся на сервисе openweathermap.org и получаем API-key.
<details>
  <summary>Мой API-key</summary>

  ```
  8ef4d6cf87e941cd535e7c370ad0a401
  ```
</details>

2. Составим запрос, соответствующий указанниям в тз (Составьте запрос на получение прогноза погоды для Симферополя с почасовым интервалом, в градусах Цельсия, на русском языке)
<details>
  <summary>Мой запрос</summary>

  ```
  http://api.openweathermap.org/data/2.5/onecall?id=524901&appid=8ef4d6cf87e941cd535e7c370ad0a401&lang=ru&units=metric&lat=44.95719&lon=34.11079&exclude=current,minutely,daily,alerts
  ```
</details>

3. Составляем запрос для получения времени в Симферополе
<details>
<summary>Мой запрос</summary>

  ```
http://worldtimeapi.org/api/timezone/Europe/Simferopol
  ```
</details>

4.  ### Создание сервера

Создаём серверное приложение. Сервер слушает get запросы на 3000 порт localhost. При определенном запросе он выдает либо html-виджет, либо обработанный json, который он получил с openweathermap и обработал. Данные хранятся в кэше, который обновляется, при устаревании.

<details>

```C++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <json/json.hpp>
#include <cpp_httplib/httplib.h>

using json = nlohmann::json;
using namespace httplib;

std::string html_str;


void json_init(const Result& res, json& new_json)
{
    if (res)
    {
        if (res->status == 200)
            new_json = json::parse(res->body);
        else
            std::cout << "Status code: " << res->status << std::endl;
    }
    else
    {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }
}

std::string current_time_str()
{
    auto current_time = std::chrono::system_clock::now();

    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
    std::string date_new;
    date_new = ctime(&current_time_t);

    std::string time_now;
    if (date_new[11] != '0')
        time_now += date_new[11];
    time_now += date_new[12];
    return time_now;
}

int current_time_int()
{
    auto current_time = std::chrono::system_clock::now();

    std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
    std::string date_new;
    date_new = ctime(&current_time_t);

    std::string time_now;
    if (date_new[11] != '0')
        time_now += date_new[11];
    time_now += date_new[12];

    return atoi(time_now.c_str());
}

void html_editing(std::string& html_str, const std::string& raw_arg, const std::string& arg)
{
    size_t position = html_str.find(raw_arg);
    while (position != std::string::npos)
    {
        html_str.replace(position, raw_arg.size(), arg);
        position = html_str.find(raw_arg, position + arg.size());
    }
}

void gen_response(const Request& req, Response& res) 
{
    html_editing(html_str, "{hourly[i].temp}", current_time_str());

    json tmp;
    std::fstream cache("cache.txt");

    if (!cache.is_open())
        std::cerr << "Error!\nFile not open\n";
    else
        cache >> tmp;

    std::string description_raw = tmp[current_time_int()]["description"].dump();
    
    std::string description;
    for (int i = 0; i < description_raw.size(); i++)
        if (description_raw[i] != char(34) && description_raw[i] != '\\')
            description += description_raw[i];

    html_editing(html_str, "{hourly[i].weather[0].description}", description);

    std::string icon_raw = tmp[current_time_int()]["icon"].dump();
    std::string icon;
    for (int i = 0; i < icon_raw.size(); i++)
        if (icon_raw[i] != char(34) && icon_raw[i] != '\\')
            icon += icon_raw[i];

    html_editing(html_str, "{hourly[i].weather[0].icon}", icon);
  
    cache.close();
    res.set_content(html_str, "text/html;charset=utf-8");
}

void gen_response_raw(const Request& req, Response& res) 
{
    std::fstream cache("cache.txt");
    std::string rawR;
    if (cache.is_open())
        getline(cache, rawR, '\0');
    else
    {
        std::cerr << "Error!\nFile not open\n";
        return;
    }
    std::string raw;
    for (int i = 0; i < rawR.length(); i++)
    {
        if (rawR[i] == '\\')
        {
            i++;
            continue;
        }
        raw += rawR[i];
    }

    res.set_content(raw, "text/plain;charset=utf-8");
}

int main() {
    Server svr;
    

    Client openweather_cli("http://api.openweathermap.org");
    auto openweather_res = openweather_cli.Get("/data/2.5/onecall?id=524901&appid=8ef4d6cf87e941cd535e7c370ad0a401&lang=ru&units=metric&lat=44.95719&lon=34.11079&exclude=current,minutely,daily,alerts");

    json openweather_json;
    json_init(openweather_res, openweather_json);
 
    Client worldtime_cli("http://worldtimeapi.org");
    auto worldtime_res = worldtime_cli.Get("/api/timezone/Europe/Simferopol");
    
    json worldtime_json;
    json_init(worldtime_res, worldtime_json);
  
    json tmp = json::array();

    json* tmp_arr = new json[48];

    for (int i = 0; i < 48; i++)
    {
        tmp_arr[i]["time"] = i;
        tmp_arr[i]["temp"] = (int)openweather_json["hourly"][i]["temp"];
        std::string  description  = openweather_json["hourly"][i]["weather"][0]["description"].dump();
        std::string icon = openweather_json["hourly"][i]["weather"][0]["icon"].dump();
        tmp_arr[i]["icon"] = icon;
        tmp_arr[i]["description"] = description;
        tmp[i] = tmp_arr[i];
    }

    delete[] tmp_arr;
    
    std::string cache_str = tmp.dump();
    std::ofstream cache("cache.txt");

    if (!cache.is_open())
        std::cerr << "Error!\nFile not open\n";
    else
        cache << cache_str;
    cache.close();

    std::ifstream html_file("widget.html");

    if (html_file.is_open())
        getline(html_file, html_str, '\0');
    else    
        std::cerr << "Error!\nFile not open\n";

    html_file.close();


    svr.Get("/", gen_response);
    svr.Get("/raw", gen_response_raw);

    std::cout << "\nStart server... OK\n";
    svr.listen("localhost", 3000);
    return 0;
}
```
</details>

5.  ### Создание клиентского приложения
Создаём клиентское приложение, которое будет посылать запросы на наш локальный сервер при помощи "requests", обрабатывать json файл с помощью модуля "json" и отображать погоду на текущий момент при помощи "Tkinter". Приложение создается на python с использованием библиотеки tkinter. 

<details>


```python
from tkinter import *
import requests
import json
import datetime


def refresh(event=None):
    try:
        res = requests.get('http://localhost:3000/raw').content.decode("utf8")
        data = json.loads(res)

        current_time = datetime.datetime.now().hour
        description.config(text=str(data[current_time]["description"]))
        temp.config(text=str((data[current_time]["temp"])) + "°C")
    except requests.exceptions.ConnectionError:
        pass


root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", refresh)
root.geometry("200x250")


top_frame = Frame(root, bg="#ffb84d", width=100, height=30)
top_frame.pack(side=TOP, fill=X)

middle_frame = Frame(root, bg="#ffffff",  width=100, height=30*3)
middle_frame.pack(expand=True, fill=BOTH)

bottom_frame = Frame(root, bg="#ffb84d", width=100, height=30)
bottom_frame.pack(side=BOTTOM, fill=X)


city = Label(top_frame, font=("Arial Bold", 12), text="Симферополь", bg="#ffb84d")
description = Label(top_frame, font=("Arial", 12), bg="#ffb84d")
temp = Label(middle_frame, font=("Arial Bold", 48), bg="#ffffff")

city.pack(pady=0)
description.pack(pady=0)
temp.pack(expand=True)

refresh()
root.mainloop()

```
=======
- Получение базового представления о взаимодействии приложений в клиент-сервеном приложении
- Изучение структуры html запроса

## Выполнение работы

##### Подготовка перед созданием программы

1. ### Регистрируемся на сервисе openweathermap.org и получаем API-ключ.
<подробности>
  <summary> Мой API-ключ </summary>

  ``
  8ef4d6cf87e941cd535e7c370ad0a401
  ``
</details>

2. ### Составим запрос, соответствующий указанниям в тз (Составьте запрос на получение прогноза погоды для Симферополя с почасовым интервалом, в градусах Цельсия, на русском языке)
<подробности>
  <summary> Мой запрос </summary>

  ``
  http://api.openweathermap.org/data/2.5/onecall?lat=44&lon=34&units=metric&exclude=current,minutely,daily,alerts&lang=ru&appid=8ef4d6cf87e941cd535e7c370ad0a401
  ``
</details>

3. ### Составляем запрос на получение времени в Симферополе
<подробности>
<summary> Мой запрос </summary>

  ``
http://worldtimeapi.org/api/timezone/Europe/Simferopol
  ``
</details>

4. ### Сервер

Создаём серверное приложение. Сервер слушает запросы на 3000 порт localhost. При определенном запросе он выдает либо html-вид, либо обработанный json, который он получил с помощью openweathermap и обработал. Данные хранятся в кэше, который обновляется, при устаревании.

<подробности>

`` С ++
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <строка>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <json / json.hpp>
#include <cpp_httplib / httplib.h>

используя json = nlohmann :: json;
используя пространство имен httplib;

std :: string html_str;


void json_init (const Result & res, json & new_json)
{
    если (res)
    {
        если (res-> status == 200)
            new_json = json :: parse (res-> body);
        еще
            std :: cout << "Код состояния:" << res-> status << std :: endl;
    }
    еще
    {
        авто ошибка = res.error ();
        std :: cout << "Код ошибки:" << err << std :: endl;
    }
}

std :: string current_time_str ()
{
    авто current_time = std :: chrono :: system_clock :: now ();

    std :: time_t current_time_t = std :: chrono :: system_clock :: to_time_t (current_time);
    std :: string date_new;
    date_new = ctime (& current_time_t);

    std :: string time_now;
    если (date_new [11]! = '0')
        time_now + = date_new [11];
    time_now + = date_new [12];
    return time_now;
}

int current_time_int ()
{
    авто current_time = std :: chrono :: system_clock :: now ();

    std :: time_t current_time_t = std :: chrono :: system_clock :: to_time_t (current_time);
    std :: string date_new;
    date_new = ctime (& current_time_t);

    std :: string time_now;
    если (date_new [11]! = '0')
        time_now + = date_new [11];
    time_now + = date_new [12];

    вернуть atoi (time_now.c_str ());
}

void html_editing (std :: string & html_str, const std :: string & raw_arg, const std :: string & arg)
{
    size_t position = html_str.find (raw_arg);
    пока (позиция! = std :: string :: npos)
    {
        html_str.replace (позиция, raw_arg.size (), arg);
        позиция = html_str.find (raw_arg, position + arg.size ());
    }
}

void gen_response (const Request и req, ответ и res) 
{
    html_editing (html_str, "{ежечасно [i] .temp}", current_time_str ());

    json tmp;
    std :: fstream cache ("cache.txt");

    если (! cache.is_open ())
        std :: cerr << "Ошибка! \ nФайл не открыт \ n";
    еще
        кеш >> tmp;

    std :: string description_raw = tmp [current_time_int ()] ["описание"]. dump ();
    
    std :: string description;
    для (int i = 0; i <description_raw.size (); i ++)
        if (description_raw [i]! = char (34) && description_raw [i]! = '\\')
            description + = description_raw [i];

    html_editing (html_str, "{ежечасно [i] .weather [0] .description}", описание);

    std :: string icon_raw = tmp [current_time_int ()] ["значок"]. dump ();
    std :: string icon;
    для (int i = 0; i <icon_raw.size (); i ++)
        если (icon_raw [i]! = char (34) && icon_raw [i]! = '\\')
            icon + = icon_raw [i];

    html_editing (html_str, "{ежечасно [i] .weather [0] .icon}", значок);
  
    cache.close ();
    res.set_content (html_str, "текст / html; charset = utf-8");
}

void gen_response_raw (const Request & req, Response & res) 
{
    std :: fstream cache ("cache.txt");
    std :: string rawR;
    если (cache.is_open ())
        getline (кеш, rawR, '\ 0');
    еще
    {
        std :: cerr << "Ошибка! \ nФайл не открыт \ n";
        возвращение;
    }
    std :: string raw;
    для (int i = 0; i <rawR.length (); i ++)
    {
        если (rawR [i] == '\\')
        {
            i ++;
            Продолжать;
        }
        raw + = rawR [я];
    }

    res.set_content (raw, «текст / простой; кодировка = utf-8»);
}

int main () {
    Сервер svr;
    

    Клиент openweather_cli ("http://api.openweathermap.org");
    auto openweather_res = openweather_cli.Get ("/ data / 2.5 / onecall? id = 524901 & appid = ff1484a9c853eaf0e82bdeee8b3cae19 & lang = ru & units = metric & lat = 44.95719 & lon = 34.11079 & exclude = текущие, минутные, ежедневные, ежедневные, ежедневные,

    json openweather_json;
    json_init (openweather_res, openweather_json);
 
    Клиент worldtime_cli ("http://worldtimeapi.org");
    auto worldtime_res = worldtime_cli.Get ("/ api / timezone / Европа / Симферополь");
    
    json worldtime_json;
    json_init (worldtime_res, worldtime_json);
  
    json tmp = json :: array ();

    json * tmp_arr = новый json [48];

    для (int я = 0; я <48; я ++)
    {
        tmp_arr [i] ["время"] = i;
        tmp_arr [i] ["temp"] = (int) openweather_json ["ежечасно"] [i] ["temp"];
        std :: string description = openweather_json ["ежечасно"] [i] ["погода"] [0] ["описание"]. dump ();
        std :: string icon = openweather_json ["ежечасно"] [я] ["погода"] [0] ["значок"]. dump ();
        tmp_arr [я] ["значок"] = значок;
        tmp_arr [i] ["description"] = описание;
        tmp [i] = tmp_arr [i];
    }

    удалить [] tmp_arr;
    
    std :: string cache_str = tmp.dump ();
    std :: ofstream cache ("cache.txt");

    если (! cache.is_open ())
        std :: cerr << "Ошибка! \ nФайл не открыт \ n";
    еще
        кеш << cache_str;
    cache.close ();

    std :: ifstream html_file ("widget.html");

    если (html_file.is_open ())
        getline (html_file, html_str, '\ 0');
    еще    
        std :: cerr << "Ошибка! \ nФайл не открыт \ n";

    html_file.close ();


    svr.Get ("/", gen_response);
    svr.Get ("/ raw", gen_response_raw);

    std :: cout << "\ nЗапустить сервер ... ОК \ n";
    svr.listen ("локальный хост", 3000);
    возврат 0;
}
``
</details>

5. ### Клиент
Создаём клиентское приложение, которое будет посылать запросы на наш локальный сервер при помощи "requests", обрабатывать json файл с помощью модуля "json" и отображать погоду на текущий момент при помощи "Tkinter". Приложение создается на python с использованием библиотеки tkinter.

<подробности>


`` питон
из tkinter import *
запросы на импорт
импортировать json
дата и время импорта


def refresh (event = None):
    пытаться:
        res = requests.get ('http: // localhost: 3000 / raw') .content.decode ("utf8")
        data = json.loads (res)

        current_time = datetime.datetime.now (). час
        description.config (text = str (данные [текущее_время] ["описание"]))
        temp.config (text = str ((data [current_time] ["temp"])) + «° C»)
    кроме request.exceptions.ConnectionError:
        проходят


корень = Tk ()
root.title ("Погода")
root.pack_propagate (0)
root.bind ("<Button-1>", обновить)
root.geometry ("200x250")


top_frame = Frame (root, bg = "# ffb84d", width = 100, height = 30)
top_frame.pack (сторона = TOP, fill = X)

middle_frame = Frame (root, bg = "# ffffff", width = 100, height = 30 * 3)
middle_frame.pack (expand = True, fill = BOTH)

bottom_frame = Кадр (корень, bg = "# ffb84d", ширина = 100, высота = 30)
bottom_frame.pack (сторона = BOTTOM, fill = X)


city ​​= Label (top_frame, font = ("Arial Bold", 12), text = "Симферополь", bg = "# ffb84d")
description = Label (top_frame, font = ("Arial", 12), bg = "# ffb84d")
temp = Label (middle_frame, font = ("Arial Bold", 48), bg = "# ffffff")

city.pack (пады = 0)
description.pack (pady = 0)
temp.pack (expand = True)

обновить ()
root.mainloop ()

``
>>>>>>> cd59c3e8db2e5ff574d0704835ecbf115fcc6726
</details>
<br>


<<<<<<< HEAD
6. ### Внешний вид HTML-виджета и python-приложения


Скриншот виджета:

![](./images/first.jpg)
*рис. 1 html-виджет*

Скриншот клиента:

![](./images/second.jpg)
*рис. 2 клиентское приложение*

## Вывод

В процессе выполнения лабораторной работы были выполнены поставленные задачи, а также формально достигнута цель данной работы - была разработка клиент-серверного приложения позволяющего узнать погоду в Симферополе на текущий момент времени, однако программа все еще требует некоторой доработки.

Разработка сервера была выполнена с использованием сторонних библиотек: cpp-httplib для работы с http запросами, json для работы с JSON файлами, re для работы с заменой шаблонных строк, time для работы со временем. Клиент использует такие библиотеки как: requests для отправки запросов, os для работы с файловой системой, tkinter для создания GUI, threading для одновременного исполнения функций.
=======

6. ### Внешний вид HTML-виджета и python-приложения


 
Скриншот виджета:

! [] (./ images / 1.jpg)
* рис. 1 html-виджет *

Скриншот клиента:

! [] (./ images / 2.jpg)
* рис. 2 клиентское приложение *

## Вывод

В процессе выполнения лабораторной работы я закрепил свои навыки работы с json и многофайловыми приложениями, получил представление об обратной стороне клиент-серверного приложения, закрепил свои знания о структуре http запроса.
>>>>>>> cd59c3e8db2e5ff574d0704835ecbf115fcc6726
