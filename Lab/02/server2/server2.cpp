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

json config;

ofstream logger("log.txt");

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

	const string templateForWebhook = u8R"(
<div class="form-row align-items-center">
    <div class="col">
        <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
    </div>
    <div class="col">
        <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
    </div>
</div>)";

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

json go_help_button =
{
    {
        {"title", u8"Помощь"},
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

json responseForArmeel(const string& text, const string& tts, const json& buttons, const json* current_session = nullptr, const bool end_session = false)
{
	json resp = {
		{"response", {
			{"buttons", buttons},
			{"end_session", end_session}
		}},
		{"version", "1.0"}
	};
	if (text != "")
	{
		resp["response"]["text"] = text;
	}
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
}

void Armeel(const Request& req, Response& res) 
{
	json request = json::parse(req.body);

	string user_id = request["session"]["application"]["application_id"];
	json resp;
	json* current_session = nullptr;

	for (auto& session : s_list)
	{
		if (session["user_id"] == user_id)
		{
			current_session = &session;
			break;
		}
	}

	string txt, tts;
	/// <summary>
	/// //////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// <param name="req"></param>
	/// <param name="res"></param>
	if (request["session"]["new"].get<bool>())
	{
		if (current_session == nullptr)
		{
			json session;
			session["user_id"] = user_id;
			session["skill_mode"] = s_exit;
			session["voice_mode"] = v_speak;
			session["korzina"] = json::array();

			s_list.push_back(session);
			current_session = &s_list[s_list.size() - 1];
		}
		else
		{
			(*current_session)["skill_mode"] = s_exit;
			(*current_session)["voice_mode"] = v_speak;
		}
		txt = u8"Здравствуйте! Я помогу вам с покупками.";
		tts = u8"Здравствуйте! Я помогу вам с покупками.";
		json response = responseForArmeel(txt, tts, go_help_button, current_session);
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
		return;
	}

	if (current_session == nullptr)
	{
		txt = u8"Произошла ошибка";
		tts = u8"Произошла ошибка";
		json response = responseForArmeel(txt, tts, go_help_button, current_session);
		res.set_content(resp.dump(2), "text/json; charset=UTF-8");
		return;
	}

	string command = request["request"]["command"];
	json response;
	if ((*current_session)["skill_mode"] == s_help)
	{
		if (command == u8"корзина")
		{
			txt = u8R"(Добавляйте товары в корзину командой 
				"Добавить в корзину <название товара и цена>",
				удаляйте из корзины командой "Удалить из корзины <название товара>"
				Просматривайте список покупок командой "Список"
				Очищайте корзину командой "Очистить корзину")";
			tts = u8R"(Добавляйте товары в корзину командой 
				"Добавить в корзину <название товара и цена>",
				удаляйте из корзины командой "Удалить из корзины <название товара>"
				Просматривайте список покупок командой "Список"
				Очищайте корзину командой "Очистить корзину")";
		}
		else if (command == u8"говорить")
		{
			txt = u8R"(Это включение голоса
				       О чем еще рассказать?)";
			tts = u8R"(Это включение голоса
				       О чем еще рассказать?)";
		}
		else if (command == u8"молчать")
		{
			txt = u8R"(Это отключение голоса
				     О чем еще рассказать?)";
			tts = u8R"(Это оключение голоса
					 О чем еще рассказать?)";
		}
		else if (command == u8"покупка завершена")
		{
			txt = u8R"(Это передача данных в эксель и очистка корзины
					   О чем еще рассказать?)";
			tts = u8R"(Это передача данных в эксель и очистка корзины
					   О чем еще рассказать?)";
		}
		else if (command == u8"сумма")
		{
			txt = u8R"(Это подсчёт суммы всех товаров в корзине
					   О чем еще рассказать?)";
			tts = u8R"(Это подсчёт суммы всех товаров в корзине
					   О чем еще рассказать?)";
		}
		else if (command == u8"выход")
		{
			txt = u8"Выход из режима помощи";
			tts = u8"Выход из режима помощи";
			(*current_session)["skill_mode"] = s_exit;
		}
		else
		{
			txt = u8"Неизвестная команда";
			tts = u8"Неизвестная команда";
		}
		if ((*current_session)["skill_mode"] == s_help)
		{
			response = responseForArmeel(txt, tts, help_buttons, current_session);
		}
		else
		{
			response = responseForArmeel(txt, tts, go_help_button, current_session);
		}
		txt = u8"О чем еще рассказать?";
		tts = u8"О чем еще рассказать?";
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
	}
	else
	{
		if (command == u8"помощь")
		{
			string txt =
				u8R"(Говорить/молчать - включает/отключает озвучивание текста Великим Эрмилем.
					 Корзина - наше новейшее изобретение для помощи с покупками. Ради нее и был сделан навык.
					 Покупка завершена - сохранение данных и очистка корзины.
					 Сумма - подсчёт стоимости всех товаров, лежащих в корзине.
					 Выйти из помощи можно при помощи команды "Выход"
					 О чём рассказать подробнее?)";
			string tts =
				u8R"(Говорить/молчать - включает/отключает озвучивание текста Великим Эрмилем.
					 Корзина - наше новейшее изобретение для помощи с покупками. Ради нее и был сделан навык.
					 Покупка завершена - сохранение данных и очистка корзины.
					 Сумма - подсчёт стоимости всех товаров, лежащих в корзине.
					 Выйти из помощи можно при помощи команды "Выход"
					 О чём рассказать подробнее?)";
			json response = responseForArmeel(txt, tts, help_buttons, current_session);
			(*current_session)["skill_mode"] = s_help;
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"молчать")
		{
			string txt = u8"Молчу, молчу";
			string tts;
			(*current_session)["voice_mode"] = v_silent;
			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"говорить")
		{
			string txt = u8"Хорошо";
			string tts = u8"Хорошо";
			(*current_session)["voice_mode"] = v_speak;
			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find(u8"добавить в корзину") == 0)
		{
			size_t size = request["request"]["nlu"]["tokens"].size();
			string txt = u8"ОК";
			string tts = u8"ОК";
			string item_name;
			int item_price = 0, num_index = 0;
			bool set_price = false;

			for (auto ent : request["request"]["nlu"]["entities"])
			{
				if (ent["type"].get<string>() == "YANDEX.NUMBER")
				{
					num_index = ent["tokens"]["start"];
					int val = ent["value"];
					if (val <= 0)
					{
						txt = u8"Если цена меньше рубля, то это уже не покупка, а подарок, наша корзина только для покупок";
						tts = u8"Если цена меньше рубля, то это уже не покупка, а подарок, наша корзина только для покупок";
					}
					else
					{
						item_price = val;
					}
					set_price = true;
					break;
				}
			}
			if (size == 3)
			{
				txt = u8"Вы не указали что добавлять";
				tts = u8"Вы не указали что добавлять";
			}
			else if (num_index == 3)
			{
				txt = u8"Вы не указали название товара";
				tts = u8"Вы не указали название товара";
			}
			else if (!set_price)
			{
				txt = u8"Вы не указали цену";
				tts = u8"Вы не указали цену";
			}
			else
			{
				for (int i = 3; i < num_index; ++i)
				{
					item_name += request["request"]["nlu"]["tokens"][i].get<string>();
					item_name += " ";
				}
				item_name.pop_back();
				json item = {
					{"item",  item_name},
					{"price", item_price}
				};
				(*current_session)["check"].push_back(item);
			}

			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find(u8"удалить из корзины") == 0)
		{
			size_t size = request["request"]["nlu"]["tokens"].size();

			string txt;
			string tts;
			string name = "";

			for (int i = 3; i < size; ++i)
			{
				name += request["request"]["nlu"]["tokens"][i].get<string>();
				name += " ";
			}
			bool found = false;
			int	item_index = 0;

			if (name == "")
			{
				txt = u8"Вы не указали название товара";
				tts = u8"Вы не указали название товара";
			}
			else
			{
				name.pop_back();
				for (auto& cart_item : (*current_session)["check"])
				{
					if (cart_item["item"].get<string>() == name)
					{
						found = true;
						break;
					}
					++item_index;
				}
				if (!found)
				{
					txt = u8"Товар не в корзине";
					tts = u8"Товар не в корзине";
				}
				else
				{
					txt = u8"Товар удалён";
					tts = u8"Товар удалён";
					(*current_session)["check"].erase((*current_session)["check"].begin() + item_index);
				}
			}
			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"очистить корзину")
		{
			string txt = u8"Корзина очищена";
			string tts = u8"Корзина очищена";
			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			(*current_session).erase("check");
			(*current_session)["check"] = json::array();
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"что в корзине")
		{
			string txt, tts;
			if ((*current_session)["check"].empty())
			{
				txt = u8"В корзине ничего нет";
				tts = u8"В корзине ничего нет";
			}
			else
			{
				txt = u8"В корзине:";
				for (auto& elem : (*current_session)["check"])
				{
					int price = elem["price"].get<int>();

					txt += "\n"
						+ elem["item"].get<string>()
						+ u8" - "
						+ std::to_string(price);

					if (price % 10 == 0)
					{
						txt += u8" рублей,";
					}
					else if (price % 10 == 1)
					{
						txt += u8" рубль,";
					}
					else if (price % 10 < 5 && price % 10 > 0)
					{
						txt += u8" рубля,";
					}
					else
					{
						txt += u8" рублей,";
					}
				}
				txt.pop_back();
				tts = txt;
			}

			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"сумма")
		{
			string txt = "";
			string tts = "";

			size_t size = request["request"]["nlu"]["tokens"].size();
			int sum = 0;
			for (auto& cart_item : (*current_session)["check"])
			{
				sum += cart_item["price"].get<int>();
			}
			txt = u8"В корзине товаров на " + std::to_string(sum);
			tts = u8"В корзине товаров на " + std::to_string(sum);
			if (sum % 10 == 0)
			{
				txt += u8" рублей";
				tts += u8" рублей";
			}
			else if (sum % 10 == 1)
			{
				txt += u8" рубль";
				tts += u8" рубль";
			}
			else if (sum % 10 < 5 && sum % 10 > 0)
			{
				txt += u8" рубля";
				tts += u8" рубля";
			}
			else
			{
				txt += u8" рублей";
				tts += u8" рублей";
			}
			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == u8"покупка завершена")
		{
			string txt = u8"Создаю список";
			string tts = u8"Создаю список";
			json output, conf;
			output["user_id"] = user_id;
			output["check"] = (*current_session)["check"];
			conf = openingConfig();

			for (string link : conf["webhooks"])
			{
				int ind = link.find('/', static_cast<string>("https://").size());
				Client cli(link.substr(0, ind).c_str());
				cli.Post(link.substr(ind, -1).c_str(), output.dump(2), "application/json; charset=UTF-8");
			}

			(*current_session).erase("check");
			(*current_session)["check"] = json::array();

			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else
		{
			string txt = u8"Неизвестная команда";
			string tts = u8"Неизвестная команда";

			json response = responseForArmeel(txt, tts, go_help_button, current_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
	}
}

int main() {
    Server svr;                            // Создаём сервер (пока-что не запущен)
    svr.Get("/webhooks", openWebhooks);
    svr.Post("/", Armeel);           // Вызвать функцию gen_response на post запрос
    svr.Post("/webhooks", webhooksPost);
    logger << u8"Сервер успешно запущен" << endl;
    cout << "OK" << endl;
    svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
    ifstream rc("webhooks.json"); //Открываем файл json 
    json RawCache = CacheReader(rc); //Запускаем функцию его читателя
    //По итогу в RawCache - json, с которым можно работать
}