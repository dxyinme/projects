#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
#pragma once

#include <mongoose/mongoose.h>
#include <cstring>
#include <string>
#include <iostream>

namespace client {
namespace httpClient {

// this class is not thread safety
class http_client {
private:

    struct mg_mgr mgr;

public:

    bool done;
    std::string s_url, s_body, content_type;
    // response body.
    std::string r_body, r_message;

    http_client();
    void HTTP_GET();
    void HTTP_POST();
    ~http_client();
};

};
};

#endif