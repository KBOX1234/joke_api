#pragma once

#include <iostream>
#include <vector>
#include <sodium.h>
#include <ctime>
#include "joke_engin.hpp"

class compliant_ip_storage {

private:
    std::time_t age;

    std::string ip_addr;

public:
    compliant_ip_storage();

    void reset_timestamp();

    void assign_ip(const std::string& ip);

    std::string get_ip();

    std::time_t get_age();

};


class user {
    private:
        std::vector<compliant_ip_storage> known_ips;

        word_bank words;

        std::string api_key;

        char hashed_password[crypto_pwhash_STRBYTES];

        std::string email;

    public:
        bool verify_password(const std::string& psw);

        int set_password(const std::string& psw);

        int add_word(const std::string& word_w, char type);

        int assign_api_key(std::string key);

        std::string get_key();

        int push_ip(std::string ip);

        int remove_old_ips();

        int assigne_email(const std::string& email_e);


        std::string serialise_to_json();


};