#ifndef MOONLIGHT_TCPCONN_H
#define MOONLIGHT_TCPCONN_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

namespace moonlight{
namespace conn{

using tcp = boost::asio::ip::tcp;

class tcp_conn {
private:
    tcp::socket socket_;
public:

    tcp_conn(boost::asio::io_service& io_service_);

    tcp::socket& socket();

    size_t read(char* buf, size_t want_len);
    
    void write(char* buf, size_t want_len);
    
    void shutdown();

    void close();

    ~tcp_conn();
};

};
};

#endif