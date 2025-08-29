#pragma once

#include <vector>
#include <iostream>

class joke_generator {
    private:
        std::vector<std::string> nouns;
        std::vector<std::string> verbs;
        std::vector<std::string> adverbs;
        std::vector<std::string> adjectives;

    public:
        std::string get_random_joke();

        void load_word_json(const std::string& fname);
};

extern joke_generator joke_engin;