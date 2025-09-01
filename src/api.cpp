//
// Created by lukers on 8/29/25.
//

#include "../include/api.hpp"
#include "../include/joke_engin.hpp"

void api_handler::joke_api() {
    svr.Get("/joke", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("{\"joke\": \"" + joke_engine.get_random_joke() + "\"}", "application/json");
    });
}

void api_handler::start() {
    joke_api();

    svr.listen("0.0.0.0", PORT);
}
