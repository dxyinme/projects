#ifndef MOONLIGHT_HANDLER_H
#define MOONLIGHT_HANDLER_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "moonlight/tcp_conn.h"

namespace moonlight{
namespace handler{

using tcp = boost::asio::ip::tcp;

class base {

private:

public:
    base();
    virtual void handle(::moonlight::conn::tcp_conn* conn_ptr);
    virtual ~base();
};

};
};

#endif