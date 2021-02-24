#ifndef MOONLIGHT_CLIENT_H
#define MOONLIGHT_CLIENT_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <mutex>

#include "moonlight/common.h"
#include "moonlight/request.h"
#include "moonlight/response.h"

namespace moonlight {
namespace client {

using tcp = boost::asio::ip::tcp;

class RPCClient {
private:

std::mutex mu_;

tcp::socket socket_;

char data_[ ::moonlight::common::BUFSIZE + 5 ];

public:

RPCClient(tcp::socket _socket);

void Call(::moonlight::request::baseRequest& request_, 
    ::moonlight::response::baseResponse& response_);

void Close();

~RPCClient();

};

};
};

#endif