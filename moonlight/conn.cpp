#include "conn.h"
#include <cstring>
#include <iostream>

namespace moonlight {
namespace server {

using tcp = boost::asio::ip::tcp;

// `socket_ = std::move(socket)` is illegal
conn::conn(tcp::socket socket, conn_pool& _conn_pool, ::moonlight::handler::handler& _handler)
    :socket_(std::move(socket)),
     conn_pool_(_conn_pool),
     handler_(_handler) {
}

void conn::start() {
    do_read();
}

void conn::stop() {
    socket_.close();
}

void conn::do_read() {
    auto self(shared_from_this());
    socket_.async_receive(boost::asio::buffer(data_, ::moonlight::common::BUFSIZE), 
        [this, self](boost::system::error_code ec, size_t length) {
            if (!ec) {
                if (length == 1) {
                    if ((uint8_t)data_[0] == ::moonlight::common::FIN) {
                        boost::system::error_code ignored_ec;
                        socket_.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ignored_ec );
                        conn_pool_.remove(shared_from_this());
                        return ;
                    }
                }
                int state = request_.parse(data_, length);
                if ( state == ::moonlight::request::parse_end ) {
                    std::cerr << "request: " << request_.bodyLength << ", " << request_.method << "\n";
                    // handle the method
                    handler_.handle(request_, response_);
                    do_write();
                } else if ( state == ::moonlight::request::parse_endless ) {
                    std::cerr << "parse endless" << "\n";
                } else if (state == ::moonlight::request::parse_bad) {
                    std::cerr << "parse bad" << "\n";
                    conn_pool_.remove(shared_from_this());
                    return ;
                } else {
                    std::cerr << "unknown" << "\n";
                    conn_pool_.remove(shared_from_this());
                    return ;
                }
            } else if (ec != boost::asio::error::operation_aborted) {
                conn_pool_.remove(shared_from_this());
                return ;
            }
        });
}

void conn::do_write() {
    auto self(shared_from_this());
    socket_.async_send(response_.to_buffers(), 
        [this, self](boost::system::error_code ec, size_t length) {
            std::cerr << "do_write: " << response_.method << ", " << response_.body.size() << "\n";
            if(!ec) {
                // boost::system::error_code ignored_ec;
                // socket_.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ignored_ec );
            }
            request_.reset();
            response_.reset();
            do_read();
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