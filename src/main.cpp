//
// Created by Luke on 29/8/2025.
//

#include "../include/joke_engin.hpp"
joke_genorator joke_engin;

int main() {
    joke_engin.load_word_json("words.json");

    for (int i = 0; i < 90000; i++) {
        std::cout << joke_engin.get_random_joke() << std::endl;
    }

    return 0;
}