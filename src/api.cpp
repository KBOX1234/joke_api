//
// Created by lukers on 8/29/25.
//

#include "../include/api.hpp"
#include "../include/joke_engin.hpp"
#include "../include/user.hpp"
#include "../include/json.hpp"
using json = nlohmann::json;

void api_handler::joke_api() {
    svr.Get("/joke", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("{\"joke\": \"" + joke_engine.get_random_joke() + "\"}", "application/json");

    });
}

void api_handler::start() {
    joke_api();

    login_api();

    submit_api();

    svr.listen("0.0.0.0", PORT);
}

void api_handler::login_api() {
    svr.Post("/login", [](const httplib::Request &req, httplib::Response &res) {
        std::cout << "got joke login\n";
        // Access POST body
        std::string body = req.body;

        std::string client_ip = req.remote_addr;

        json body_json = json::parse(body);

        if (!body_json.contains("email") || !body_json.contains("password")) {
            res.set_content("error", "text/plain");
        }
        else {
            json response;

            std::string key = user_manager.login(body_json["email"], body_json["password"], client_ip);

            std::cout << key << std::endl;

            if (key != "no_key") {

                response["key"] = key;

                res.set_content(response.dump(), "application/json");
            }
            else {
                res.set_content("{\"key\": \"error\"}", "application/json");
            }

        }


    });

    svr.Post("/sign_in", [](const httplib::Request &req, httplib::Response &res) {
        std::cout << "got joke signin\n";
        // Access POST body
        std::string body = req.body;

        std::string client_ip = req.remote_addr;

        json body_json = json::parse(body);

        if (!body_json.contains("email") || !body_json.contains("password")) {
            res.set_content("error", "text/plain");
        }
        else {
            json response;

            std::string key = user_manager.sign_up(body_json["email"], body_json["password"], client_ip);

            if (key != "no_key") {

                response["key"] = key;

                std::cout << key << std::endl;

                res.set_content(response.dump(), "application/json");
            }
            else {
                res.set_content("{\"key\": \"error\"}", "application/json");
            }

        }


    });
}

void api_handler::submit_api() {
    svr.Post("/submit", [](const httplib::Request &req, httplib::Response &res) {
        std::cout << "got submit\n";
        // Access POST body
        std::string body = req.body;

        json body_json = json::parse(body);

        if (!body_json.contains("key") || !body_json.contains("word") || !body_json.contains("type")) {
            res.set_content("error", "text/plain");
        }
        else {
            json response;

            char type;

            if (body_json["type"] == "noun") type = NOUN;
            if (body_json["type"] == "verb") type = VERB;
            if (body_json["type"] == "adverb") type = ADVERB;
            if (body_json["type"] == "adjective") type = ADJECTIVES;

            int res = user_manager.add_word(body_json["word"], type, body_json["key"]);

            if (res >= 0) {
                response["status"] = "good";

                std::cout << body_json["word"] <<std::endl;
            }
            else {
                response["status"] = "bad";
            }

        }


    });
}


