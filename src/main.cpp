//
// Created by Luke on 29/8/2025.
//

#include "../include/joke_engin.hpp"
#include "../include/httplib.h"
#include "../include/api.hpp"
#include "../include/user.hpp"

api_handler api;

joke_generator joke_engine;  // global

user_master user_manager;

int main() {
    joke_engine.load_word_json("words.json");

    api.start();
}
