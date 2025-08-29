//
// Created by Luke on 29/8/2025.
//

#include "../include/joke_engin.hpp"
#include <random>

std::string joke_genorator::get_random_joke() {
    std::random_device rd;
    std::mt19937 gen(rd());


    std::uniform_int_distribution<> nound(1, nouns.size());
    int noun = nound(gen) - 1;

    std::uniform_int_distribution<> pronound(1, pronouns.size());
    int pronoun = pronound(gen) - 1;

    std::uniform_int_distribution<> verbd(1, verbs.size());
    int verb = verbd(gen) - 1;

    std::uniform_int_distribution<> adverbd(1, adverbs.size());
    int adverb = adverbd(gen) - 1;

    std::uniform_int_distribution<> adjectived(1, adjectives.size());
    int adjective = adjectived(gen) - 1;

    std::string noun_s = nouns[noun];
    std::string pronoun_s = pronouns[pronoun];
    std::string verb_s = verbs[verb];
    std::string adverb_s = adverbs[adverb];
    std::string adjective_s = adjectives[adjective];



}
