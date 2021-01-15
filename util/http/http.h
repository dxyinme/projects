#ifndef HTTP_H
#define HTTP_H
#pragma once

#include <cstring>
#include <unordered_map>

namespace http {


class Server {
private:

public:

    Server(){}

    int listen_and_serve(const char* addr);

    ~Server(){}

};

class Client {

};

};

#endif