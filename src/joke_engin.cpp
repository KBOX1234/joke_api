//
// Created by Luke on 29/8/2025.
//

#include "../include/joke_engin.hpp"
#include <random>
#include "../include/json.hpp"
using json = nlohmann::json;
#include "../include/io.hpp"

std::string joke_generator::get_random_joke() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> nound(1, nouns.size());
    int noun = nound(gen) - 1;
    int noun2 = nound(gen) - 1;


    std::uniform_int_distribution<> verbd(1, verbs.size());
    int verb = verbd(gen) - 1;

    std::uniform_int_distribution<> adverbd(1, adverbs.size());
    int adverb = adverbd(gen) - 1;

    std::uniform_int_distribution<> adjectived(1, adjectives.size());
    int adjective = adjectived(gen) - 1;

    std::uniform_int_distribution<> use_pro_noun(1, 4);
    int use_pronoun = use_pro_noun(gen);

    int use_adjective = use_pro_noun(gen);

    int use_adverb = use_pro_noun(gen);

    std::string noun_s = nouns[noun];
    std::string noun_s2 = nouns[noun2];
    std::string verb_s = verbs[verb];
    std::string adverb_s = adverbs[adverb];
    std::string adjective_s = adjectives[adjective];

    std::string joke = "why did ";

    if (use_adjective == 1) {
        joke = joke + "the " + adjective_s + " ";
    }

    joke = joke + noun_s + " ";

    if (use_adverb == 1) {
        joke = joke + adverb_s + " ";
    }

    joke = joke + verb_s + " " + noun_s2 + "?";

    return joke;
}


void joke_generator::load_word_json(const std::string &fname) {

    std::string json_str = easy_file_ops::load_text_file(fname);

    json json_obj = json::parse(json_str);

    json noun_j = json_obj["nouns"];
    json verb_j = json_obj["verbs"];
    json adverb_j = json_obj["adverbs"];
    json adjective_j = json_obj["adjectives"];

    for (int i = 0; i < noun_j.size(); i++) {
        nouns.push_back(noun_j[i]);
    }

    for (int i = 0; i < verb_j.size(); i++) {
        verbs.push_back(verb_j[i]);
    }

    for (int i = 0; i < adverb_j.size(); i++) {
        adverbs.push_back(adverb_j[i]);
    }

    for (int i = 0; i < adjective_j.size(); i++) {
        adjectives.push_back(adjective_j[i]);
    }
}
