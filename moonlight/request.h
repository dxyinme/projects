#ifndef MOONLIGHT_REQUEST_H
#define MOONLIGHT_REQUEST_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_set>
#include <boost/asio.hpp>
#include <string>
#include <cstring>

namespace moonlight {
namespace request {
const int parse_end     = 20011;
const int parse_endless = 20012;
const int parse_bad     = 20013;

uint32_t bytes_to_u32(uint8_t* ch);

/*
    baseRequest :
        |       methodname       |\r\n| bodyLength | body |
        |   isalpha, (0,1024]    |  2 |   size_t   | body |
*/
class baseRequest {
private:
    bool is_method;
public:
    std::string body;
    std::string method;
    size_t bodyLength;
    baseRequest();
    int parse(char* ch, size_t length);
    ~baseRequest();
};


};
};

#endif