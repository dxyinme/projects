#include "conn.h"
#include <cstring>
#include <iostream>

namespace moonlight {
namespace server {

using tcp = boost::asio::ip::tcp;

// `socket_ = std::move(socket)` is illegal
conn::conn(tcp::socket socket, conn_pool& _conn_pool)
    :socket_(std::move(socket)),
     conn_pool_(_conn_pool) {
}

void conn::start() {
    do_read();
}

void conn::stop() {
    socket_.close();
}

void conn::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, BUFSIZE), 
        [this, self](boost::system::error_code ec, size_t length) {
            if (!ec) {
                int state = request_.parse(data_, length);
                if ( state == ::moonlight::parse_end ) {
                    std::cerr << request_.bodyLength << "\n";
                    std::cerr << request_.method << "\n";
                } else if ( state == ::moonlight::parse_endless ) {
                    do_read();
                } else if (state == ::moonlight::parse_bad) {
                    std::cerr << "parse bad" << "\n";
                    conn_pool_.remove(shared_from_this());
                } else {
                    std::cerr << "unknown" << "\n";
                    conn_pool_.remove(shared_from_this());
                }
            } else if (ec !=  boost::asio::error::operation_aborted) {
                conn_pool_.remove(shared_from_this());
            }
        });
}

void conn::do_write() {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, strlen(data_)), 
        [this, self](boost::system::error_code ec, size_t length) {
            if(!ec) {
                boost::system::error_code ignored_ec;
                socket_.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ignored_ec );
            } else if (ec != boost::asio::error::operation_aborted) {
                conn_pool_.remove(shared_from_this());
            }

        });
}

conn::~conn() {}


conn_pool::conn_pool() {}

void conn_pool::add(conn_ptr ptr) {
    conn_set.insert(ptr);
    ptr->start();
}

void conn_pool::remove(conn_ptr ptr) {
    ptr -> stop();
    conn_set.erase(ptr);
}

void conn_pool::stop_all() {
    for (auto v : conn_set) {
        v -> stop();
    }
}

conn_pool::~conn_pool() {}

};
};