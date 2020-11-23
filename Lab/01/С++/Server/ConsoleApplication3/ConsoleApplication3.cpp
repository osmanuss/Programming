#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "include/json/json.hpp"
#include "include/cpp_httplib/httplib.h""

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