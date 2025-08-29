//
// Created by Luke on 29/8/2025.
//

#include "../include/joke_engin.hpp"
#include "../include/httplib.h"

joke_generator joke_engin;  // global

int main() {
    joke_engin.load_word_json("words.json");

    httplib::Server svr;

    svr.Get("/joke", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("{\"joke\": \"" + joke_engin.get_random_joke() + "\"}", "application/json");
    });

    svr.listen("0.0.0.0", 8080);
}
