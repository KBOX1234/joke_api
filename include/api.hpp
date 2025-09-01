//
// Created by lukers on 8/29/25.
//

#include "httplib.h"

#define PORT 3214

class api_handler {
    private:
        httplib::Server svr;

        void joke_api();

        void login_api();

        void submit_api();

        void image_api();

    public:
        void start();
};

extern api_handler api;