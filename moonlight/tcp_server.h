#ifndef MOONLIGHT_TCPSERVER_H
#define MOONLIGHT_TCPSERVER_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <cstring>
#include <future>

#include <boost/asio.hpp>

#include "moonlight/tcp_conn.h"
#include "moonlight/handler.h"

namespace moonlight{
namespace server{

using tcp = boost::asio::ip::tcp;

class tcp_server {
private:
    boost::asio::io_service io_service_;
    
    tcp::acceptor acceptor_;

    std::vector<std::unique_ptr<boost::asio::io_service::work> > io_service_work_pool;

    std::vector<std::thread> th_pool;

    std::vector<std::unique_ptr<boost::asio::io_service> > io_service_pool;

    size_t currency_, pool_index;

    moonlight::handler::base* handler_;

    boost::asio::io_service& select_io_service();

    void do_accept();

public:

    tcp_server(std::string addr, int port, size_t currency_ = 5);

    void stop();

    void run();

    ~tcp_server();
};

};
};

#endif