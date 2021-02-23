#ifndef MOONLIGHT_HANDLER_H
#define MOONLIGHT_HANDLER_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_set>
#include <boost/asio.hpp>
#include <string>
#include <cstring>

#include "moonlight/response.h"
#include "moonlight/request.h"

namespace moonlight {
namespace handler {

class handler {
private:

public:

    handler();

    void handle(const ::moonlight::request::baseRequest& base_request_, 
        ::moonlight::response::baseResponse& base_response_);

    ~handler();

};


};
};

#endif