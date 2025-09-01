//
// Created by lukers on 9/1/25.
//

#include "../include/user.hpp"

#include "../include/api.hpp"
#include "../include/json.hpp"
using json = nlohmann::json;

void compliant_ip_storage::assign_ip(const std::string &ip) {
    ip_addr = ip;
}

void compliant_ip_storage::reset_timestamp() {
    time(&age);
}

std::string compliant_ip_storage::get_ip() {
    return ip_addr;
}

time_t compliant_ip_storage::get_age() {
    return age;
}


compliant_ip_storage::compliant_ip_storage() {
    time(&age);
}

int user::add_word(const std::string &word_w, char type) {
    if (type == NOUN) {
        words.add_noun(word_w);
        return 0;
    }
    if (type == VERB) {
        words.add_verb(word_w);
        return 0;
    }
    if (type == ADVERB) {
        words.add_adverb(word_w);
        return 0;
    }
    if (type == ADJECTIVES) {
        words.add_adjective(word_w);
        return 0;
    }

    return -1;
}

int user::assign_api_key(std::string key) {
    api_key = key;
}

int user::assigne_email(const std::string &email_e) {
    email = email_e;
}

std::string user::get_key() {
    return api_key;
}

int user::push_ip(std::string ip) {
    for (unsigned long i = 0; i < known_ips.size(); i++) {
        if (known_ips[i].get_ip() == ip) {
            known_ips[i].reset_timestamp();
        }
    }

    compliant_ip_storage new_ip;
    new_ip.assign_ip(ip);

    known_ips.push_back(new_ip);

    return 0;
}

int user::remove_old_ips() {
    std::time_t now = std::time(nullptr);

    for (unsigned long i = 0; i < known_ips.size(); i++) {
        double diff_seconds = std::difftime(now, known_ips[i].get_age());

        double diff_days = diff_seconds / (60 * 60 * 24);

        if (diff_days >= 29) {
            known_ips.erase(known_ips.begin() + i);
        }
    }

    return 0;
}

int user::set_password(const std::string &psw) {
    if (crypto_pwhash_str(
        hashed_password,
        psw.c_str(),
        psw.size(),
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {

            return -1;

        }

    return 0;
}

bool user::verify_password(const std::string &psw) {
    if (crypto_pwhash_str_verify(hashed_password, psw.c_str(), psw.size()) == 0) {
        return true;
    }

    return false;
}

std::string user::serialise_to_json() {
    json j_obj;

    j_obj["pswd"] = hashed_password;

    j_obj["email"] = email;

    j_obj["words"] = json::parse(words.serialise_to_json());
    for (unsigned long i = 0; i < known_ips.size(); i++) {
        json tmp_j;

        tmp_j["age"] = known_ips[i].get_age();
        tmp_j["ip"] = known_ips[i].get_ip();

        j_obj["known_ips"][i] = tmp_j;
    }

    return j_obj.dump(4);
}
