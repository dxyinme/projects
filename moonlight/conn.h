#ifndef MOONLIGHT_SERVER_CONN_H
#define MOONLIGHT_SERVER_CONN_H
#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <unordered_set>
#include <boost/asio.hpp>

#include "moonlight/request.h"
#include "moonlight/response.h"
#include "moonlight/handler.h"


namespace moonlight {
namespace server {

using tcp = boost::asio::ip::tcp;

const int BUFSIZE = 4096;

class conn_pool;

class conn : public std::enable_shared_from_this<conn> {
public:
    conn(tcp::socket socket, conn_pool& _conn_pool, ::moonlight::handler::handler& _handler);
    void start();
    void stop();
    ~conn();
private:
    tcp::socket socket_;
    
    conn_pool& conn_pool_;

    ::moonlight::request::baseRequest request_;

    ::moonlight::response::baseResponse response_;

    ::moonlight::handler::handler& handler_;

    char data_[BUFSIZE];

    void do_read();

    void do_write();
};

typedef std::shared_ptr<conn> conn_ptr;

class conn_pool {

public:
    conn_pool();

    void add(conn_ptr item);

    void remove(conn_ptr item);

    void stop_all();

    ~conn_pool();

private:
    std::unordered_set<conn_ptr> conn_set;

};

};
};

#endif