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

    for (unsigned long i = 0; i < noun_j.size(); i++) {
        nouns.push_back(noun_j[i]);
    }

    for (unsigned long i = 0; i < verb_j.size(); i++) {
        verbs.push_back(verb_j[i]);
    }

    for (unsigned long i = 0; i < adverb_j.size(); i++) {
        adverbs.push_back(adverb_j[i]);
    }

    for (unsigned long i = 0; i < adjective_j.size(); i++) {
        adjectives.push_back(adjective_j[i]);
    }
}
//haha funny because obs
std::string word::serialize_to_json() {
    json j_obs;

    j_obs["age"] = age;
    j_obs["word"] = word_str;

    j_obs.dump();
}

void word_bank::add_adjective(const std::string &word_w) {
    word new_word;

    time(&new_word.age);

    new_word.word_str = word_w;

    adjectives.push_back(new_word);
}

void word_bank::add_adverb(const std::string &word_w) {
    word new_word;

    time(&new_word.age);

    new_word.word_str = word_w;

    adverbs.push_back(new_word);
}

void word_bank::add_verb(const std::string &word_w) {
    word new_word;

    time(&new_word.age);

    new_word.word_str = word_w;

    verbs.push_back(new_word);
}

void word_bank::add_noun(const std::string &word_w) {
    word new_word;

    time(&new_word.age);

    new_word.word_str = word_w;

    nouns.push_back(new_word);
}

word word_bank::get_first_word_instance(const std::string &word_w) {
    for (unsigned long i = 0; i < nouns.size(); i++) {
        if (nouns[i].word_str == word_w) {
            return nouns[i];
        }
    }
    for (unsigned long i = 0; i < verbs.size(); i++) {
        if (verbs[i].word_str == word_w) {
            return verbs[i];
        }
    }
    for (unsigned long i = 0; i < adverbs.size(); i++) {
        if (adverbs[i].word_str == word_w) {
            return adverbs[i];
        }
    }
    for (unsigned long i = 0; i < adjectives.size(); i++) {
        if (adjectives[i].word_str == word_w) {
            return adjectives[i];
        }
    }

    word f;
    f.age = 0;

    return f;


}

word word_bank::get_latest_word_instance(const std::string &word_w) {
    for (unsigned long i = nouns.size() - 1; i > 0; i--) {
        if (nouns[i].word_str == word_w) {
            return nouns[i];
        }
    }
    for (unsigned long i = verbs.size() - 1; i > 0; i--) {
        if (verbs[i].word_str == word_w) {
            return verbs[i];
        }
    }
    for (unsigned long i = adverbs.size() - 1; i > 0; i--) {
        if (adverbs[i].word_str == word_w) {
            return adverbs[i];
        }
    }
    for (unsigned long i = adjectives.size() - 1; i > 0; i--) {
        if (adjectives[i].word_str == word_w) {
            return adjectives[i];
        }
    }

    word f;
    f.age = 0;

    return f;
}

std::string word_bank::serialise_to_json() {
    json j_obj;

    for (unsigned long i = 0; i < nouns.size(); i++) {
        j_obj["nouns"][i] = nouns[i].serialize_to_json();
    }
    for (unsigned long i = 0; i < adverbs.size(); i++) {
        j_obj["adverbs"][i] = adverbs[i].serialize_to_json();
    }
    for (unsigned long i = 0; i < verbs.size(); i++) {
        j_obj["verbs"][i] = verbs[i].serialize_to_json();
    }
    for (unsigned long i = 0; i < adjectives.size(); i++) {
        j_obj["adjectives"][i] = adjectives[i].serialize_to_json();
    }

    return j_obj.dump(4);
}

int word_bank::word_count(const std::string &word_w) {
    int count = 0;
    for (unsigned long i = nouns.size() - 1; i > 0; i--) {
        if (nouns[i].word_str == word_w) {
            count++;
        }
    }
    for (unsigned long i = verbs.size() - 1; i > 0; i--) {
        if (verbs[i].word_str == word_w) {
            count++;
        }
    }
    for (unsigned long i = adverbs.size() - 1; i > 0; i--) {
        if (adverbs[i].word_str == word_w) {
            count++;
        }
    }
    for (unsigned long i = adjectives.size() - 1; i > 0; i--) {
        if (adjectives[i].word_str == word_w) {
            count++;
        }
    }

}

void joke_generator::add_word(const std::string &word, char type) {
    if (type == NOUN) {
        nouns.push_back(word);
    }
    if (type == VERB) {
        verbs.push_back(word);
    }
    if (type == ADVERB) {
        adverbs.push_back(word);
    }
    if (type == ADJECTIVES) {
        adjectives.push_back(word);
    }
}
