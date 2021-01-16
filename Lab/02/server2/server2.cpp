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
const string webList = "{webhooks_list}";
const string urlka = "{Webhook URL}";
const string templateForWebhook = u8R"(
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

json openingConfig()
{
    ifstream cache("config.json");
    json config;
    logger << u8"Попытка открыть конфигурационный файл" << endl;
    if (cache.is_open())
    {
        cache >> config;
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

/*json gen_response(const string& text, const string& tts, const json& buttons, const json* current_session = nullptr, const bool end_session = false)
{
    json resp = {
        {"response", {
            {"buttons", buttons},
            {"end_session", end_session}
        }},
        {"version", "1.0"}
    };

    resp["response"]["text"] = text;

    if (current_session != nullptr && (*current_session)["voice_mode"] == v_speak)
    {
        if (tts != "")
        {
            resp["response"]["tts"] = tts;
        }
        resp["response"]["buttons"].push_back(silent_button);
    }
    else if (current_session != nullptr && (*current_session)["voice_mode"] == v_silent)
    {
        resp["response"]["buttons"].push_back(speak_button);
    }
    return resp;
}*/

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

string genWebhook()
{
    string webhooks_template, Webhooks;
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
        config = openingConfig();
    }

    int size = config["webhooks"].size();
    if (size)
    {
        for (int i = 0; i < size; i++)
        {
            string site = config["webhooks"][i];
            string OneWebhook = templateForWebhook;
            OneWebhook.replace(OneWebhook.find(urlka), urlka.length(), site);
            OneWebhook.replace(OneWebhook.find(urlka), urlka.length(), site);
            Webhooks = Webhooks + OneWebhook;
        }
        webhooks_template.replace(webhooks_template.find(webList), webList.length(), Webhooks);
    }
    else
    {
        webhooks_template.replace(webhooks_template.find(webList), webList.length(), "");
    }
    return webhooks_template;
}

void openWebhooks(const Request& req, Response& res)
{
    string output = genWebhook();
    res.set_content(output, "text/html");
}

void savingConfig(json config)
{
    ofstream cache("config.json");

    if (cache.is_open())
    {
        cache << config.dump(4);
        cache.close();
        logger << u8"Конфигурационный файл успешно обновлён" << endl;
    }
    else
    {
        logger << u8"Не удалось открыть конфигурационный файл" << endl;
    }
}

void webhooksPost(const Request& req, Response& res)
{
    if (config.empty())
    {
        config = openingConfig();
    }

    if (req.has_param("del"))
    {
        string removing = req.get_param_value("del");
        int size = config["webhooks"].size();
        for (int i = 0; i < size; i++)
        {
            string webhook = config["webhooks"][i];
            if (webhook == removing)
            {
                config["webhooks"].erase(config["webhooks"].begin() + i);
                logger << u8"Был удалён вебхук " << webhook << endl;
                break;
            }
        }
    }
    else if (req.has_param("set"))
    {
        string adding = req.get_param_value("set");
        if (adding == "")
        {
            logger << u8"Получен запрос на добавление пустого вебхука" << endl;
        }
        else
        {
            logger << u8"Получен запрос на добавление вебхука " << adding << endl;
            int size = config["webhooks"].size();
            bool exist = false;
            if (size)
            {
                for (int i = 0; i < size; i++)
                {
                    string webhook = config["webhooks"][i];
                    if (webhook == adding)
                    {
                        logger << u8"Этот вебхук уже существует" << webhook << endl;
                        exist = true;
                        break;
                    }
                }
            }
            if (!exist)
            {
                logger << u8"Был добавлен вебхук " << adding << endl;
                config["webhooks"].push_back(adding);
            }
        }
    }
    savingConfig(config);
    string output = genWebhook();
    res.set_content(output, "text/html; charset=UTF-8");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum voice_mode
{
    v_silent,
    v_speak
};
enum skill_mode
{
    s_help,
    s_exit
};

json s_list = json::array();

json help_buttons =
{
    {
        {"title", u8"Корзина"},
        {"hide", true}
    },
    {
        {"title", u8"Молчать"},
        {"hide", true}
    },
    {
        {"title", u8"Говорить"},
        {"hide", true}
    },
    {
        {"title", u8"Сумма"},
        {"hide", true}
    },
    {
        {"title", u8"Покупка завершена"},
        {"hide", true}
    },
    {
        {"title", u8"Выход"},
        {"hide", true}
    }
};

json silent_button =
{
    {"title", u8"Молчать"},
    {"hide", true}
};

json speak_button =
{
    {"title", u8"Говорить"},
    {"hide", true}
};

json go_help_button =
{
    {
        {"title", u8"Помощь"},
        {"hide", true}
    }
};



int main() {
    Server svr;                            // Создаём сервер (пока-что не запущен)
    svr.Get("/webhooks", openWebhooks);
    svr.Post("/", gen_response);           // Вызвать функцию gen_response на post запро
    svr.Post("/webhooks", webhooksPost);
    logger << u8"Сервер успешно запущен" << endl;
    svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
    ifstream rc("webhooks.json"); //Открываем файл json 
    json RawCache = CacheReader(rc); //Запускаем функцию его читателя
    //По итогу в RawCache - json, с которым можно работать
}