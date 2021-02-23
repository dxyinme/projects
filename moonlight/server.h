#ifndef MOONLIGHT_SERVER_H
#define MOONLIGHT_SERVER_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "conn.h"

namespace moonlight {
namespace server {

using tcp = boost::asio::ip::tcp;

class RPCServer {
private:

    tcp::acceptor acceptor_;

    tcp::socket socket_;

    conn_pool conn_pool_;

    boost::asio::io_service& io_service_;

    ::moonlight::handler::handler handler_;

public:

RPCServer(boost::asio::io_service& io_service, int port);

void do_accept();

void run();

~RPCServer();

};

};
};

#endif