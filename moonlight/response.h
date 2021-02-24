#ifndef MOONLIGHT_RESPONSE_H
#define MOONLIGHT_RESPONSE_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_set>
#include <boost/asio.hpp>
#include <string>
#include <cstring>
#include <vector>
#include <boost/lexical_cast.hpp>

#include "moonlight/common.h"

namespace moonlight {
namespace response {

void u32_to_bytes(uint8_t* ch, uint32_t val);

class baseResponse {
private:

public:
    std::string body;
    std::string method;
    baseResponse();
    void reset();
    std::vector<boost::asio::const_buffer> to_buffers();
    ~baseResponse();
};


};
};

#endif