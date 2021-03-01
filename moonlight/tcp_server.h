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

namespace moonlight{
namespace server{

using tcp = boost::asio::ip::tcp;

class tcp_server {
private:
    boost::asio::io_service io_service_;
    
    tcp::acceptor acceptor_;
    
    std::vector<std::unique_ptr<boost::asio::io_service> > io_service_pool;
    
    size_t concurrency_, pool_index;

    void do_accept();
    
    boost::asio::io_service& get_one_io_service();

public:

    tcp_server(std::string addr, int port, size_t concurrency = 1);

    void stop();

    void run();

    ~tcp_server();
};

};
};

#endif