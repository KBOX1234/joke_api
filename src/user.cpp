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

    return 0;
}

int user::assigne_email(const std::string &email_e) {
    email = email_e;

    return 0;
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

void user_master::add_or_increase_ip_count(const std::string &ip) {
    for (unsigned long i = 0; i < ip_checker.size(); i++) {
        if (ip_checker[i].ip == ip) {
            ip_checker[i].count++;
            return;
        }
    }
    ip_use_count i;
    i.count = 0;
    i.ip = ip;

    ip_checker.push_back(i);
}

int user_master::add_word(const std::string word_w, char type, std::string key) {
    for (unsigned int i = 0; i < users.size(); i++) {
        if (users[i].get_key() == key) {
            users[i].add_word(word_w, type);

            return 0;
        }
    }

    return -1;
}

bool user_master::is_ip_maxed(const std::string &ip) {
    for (unsigned int i = 0; i < ip_checker.size(); i++) {
        if (ip_checker[i].ip == ip) {
            if (ip_checker[i].count >= MAX_ACCOUNTS_PER_IP) return true;
            return false;
        }
    }

    return false;
}

std::string user::get_email() {
    return email;
}


std::string user_master::login(const std::string &email, const std::string &password, const std::string &ip) {

    user* existing_user;

    for (unsigned int i = 0; i < users.size(); i++) {
        if (users[i].get_email() == email) {
            existing_user = &users[i];
        }
    }

    if (existing_user->verify_password(password) == true) {
        unsigned char key[MAX_KEY_LENGTH + 1];

        const char charset[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789";

        for (size_t i = 0; i < MAX_KEY_LENGTH - 1; i++) {
            unsigned char r;
            randombytes_buf(&r, 1);
            key[i] = charset[r % (sizeof(charset) - 1)];
        }
        key[MAX_KEY_LENGTH - 1] = '\0';


        key[MAX_KEY_LENGTH] = '\0';

        std::string n_key(reinterpret_cast<char*>(key));

        existing_user->assign_api_key(n_key);

        existing_user->push_ip(ip);



        return n_key;
    }

    return "no_key";
}

std::string user_master::sign_up(const std::string &email, const std::string &password, const std::string &ip) {
    if (is_ip_maxed(ip)) {
        return "no_key";
    }

    user new_user;

    new_user.assigne_email(email);

    new_user.set_password(password);

    unsigned char key[MAX_KEY_LENGTH + 1];

    const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";

    for (size_t i = 0; i < MAX_KEY_LENGTH - 1; i++) {
        unsigned char r;
        randombytes_buf(&r, 1);
        key[i] = charset[r % (sizeof(charset) - 1)];
    }
    key[MAX_KEY_LENGTH - 1] = '\0';


    key[MAX_KEY_LENGTH] = '\0';

    std::string n_key(reinterpret_cast<char*>(key));

    new_user.assign_api_key(n_key);

    add_or_increase_ip_count(ip);

    new_user.push_ip(ip);

    users.push_back(new_user);


    return n_key;

}


