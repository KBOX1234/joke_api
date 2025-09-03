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

        void add_word(const std::string& word, char type);
};

#define NOUN 0
#define VERB 1
#define ADVERB 2
#define ADJECTIVES 3

class word {
public:

    time_t age;

    std::string word_str;

    std::string serialize_to_json();
};

class word_bank {

private:
    std::vector<word> nouns;
    std::vector<word> verbs;
    std::vector<word> adverbs;
    std::vector<word> adjectives;

public:

    void add_noun(const std::string& word_w);
    void add_verb(const std::string& word_w);
    void add_adverb(const std::string& word_w);
    void add_adjective(const std::string& word_w);

    int word_count(const std::string& word_w);

    word get_latest_word_instance(const std::string& word_w);

    word get_first_word_instance(const std::string& word_w);

    word get_word(const std::string& word_w, int instance);

    std::string serialise_to_json();

};

extern joke_generator joke_engine;