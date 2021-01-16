#include <iostream>
#include <string>
#include <iomanip>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>

using namespace httplib;
using json = nlohmann::json;
using std::endl;
using std::cout;
using std::string;
using std::ofstream;
using std::ifstream;
const string replacerfull = "{webhooks_list}";
const string replacerone = "{Webhook URL}";
const string OneWebhookTemplate = u8R"(
<div class="form-row align-items-center">
    <div class="col">
        <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
    </div>
    <div class="col">
        <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
    </div>
</div>)";

ofstream logger("log.txt");

json config;

json config_open()
{
    ifstream config_cache("config.json");
    json config;
    logger << u8"Попытка открыть конфигурационный файл" << endl;
    if (config_cache.is_open())
    {
        config_cache >> config;
        logger << u8"Конфигурационный файл десериализирован" << endl;
    }
    else
    {
        logger << u8"Не удалость открыть конфигурационный файл" << endl;
        config["webhooks"] = json::array();
        logger << u8"Был создан json с пустым массивом" << endl;
    }

    return config;
}

bool is_empty_file(std::ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof(); // т.е. если мы взяли "конец файла", то вернётся true
}

void gen_response(const Request& req, Response& res) {
    // Выводим на экран тело запроса
    std::cout << req.body.c_str();
    // Здесь будет ответ, пока-что взят пример из документации
    std::string str = u8R"(
    {
      "response": {
        "text": "Здравствуйте! Это мы, хороводоведы.",
        "tts": "Здравствуйте! Это мы, хоров+одо в+еды.",
        "buttons": [
            {
                "title": "Надпись на кнопке",
                "payload": {},
                "url": "https://example.com/",
                "hide": true
            }
        ],
        "end_session": false
      },
      "version": "1.0"
    })";
    // Отправляем ответ
    res.set_content(str, "text/json; charset=UTF-8");
}

json CacheGenerator(ifstream& ReadCache)
{
    json RawCache;
    RawCache = u8R"(
{
    "webhooks":[]
}
)"_json;
    ofstream wc("webhooks.json");
    cout << "Generating cache..." << endl;
    wc << std::setw(2) << RawCache << std::endl;

    return RawCache;
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

string gen_webhook_page()
{
    string webhooks_template, AllWebHooks;
    ifstream webhooks_cache("webhooks_template.html");

    if (webhooks_cache.is_open())
    {
        getline(webhooks_cache, webhooks_template, '\0');
        webhooks_cache.close();
    }
    else
    {
        logger << u8"Не удалось открыть шаблон сайта" << endl;
        return "";
    }

    if (config.empty())
    {
        config = config_open();
    }

    int size = config["webhooks"].size();
    if (size)
    {
        for (int i = 0; i < size; i++)
        {
            string site = config["webhooks"][i];
            string OneWebhook = OneWebhookTemplate;
            OneWebhook.replace(OneWebhook.find(replacerone), replacerone.length(), site);
            OneWebhook.replace(OneWebhook.find(replacerone), replacerone.length(), site);
            AllWebHooks = AllWebHooks + OneWebhook;
        }
        webhooks_template.replace(webhooks_template.find(replacerfull), replacerfull.length(), AllWebHooks);
    }
    else
    {
        webhooks_template.replace(webhooks_template.find(replacerfull), replacerfull.length(), "");
    }
    return webhooks_template;
}

void webhooks_page(const Request& req, Response& res)
{
    string output = gen_webhook_page();
    res.set_content(output, "text/html");
}

int main() {
    Server svr;                            // Создаём сервер (пока-что не запущен)
    svr.Get("/webhooks", webhooks_page);
    svr.Post("/", gen_response);           // Вызвать функцию gen_response на post запрос
    std::cout << "Start server... OK\n"; // cout использовать нельзя
    svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
    ifstream rc("webhooks.json"); //Открываем файл json 
    json RawCache = CacheReader(rc); //Запускаем функцию его читателя
    //По итогу в RawCache - json, с которым можно работать
}