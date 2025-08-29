#pragma once
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


#define NOFILE "iul84y0ufp"
#define STRERROR "hdlslonfe"

class easy_file_ops{
    public:
        static std::string load_text_file(std::string filename);

        static int save_to_text_file(std::string data, std::string filename);
};
