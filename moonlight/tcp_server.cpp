#include "tcp_server.h"

#include "moonlight/tcp_conn.h"
#include <thread>

namespace moonlight{
namespace server{

using tcp = boost::asio::ip::tcp;

tcp_server::tcp_server(std::string addr, int port, size_t concurrency)
    : io_service_(), 
    acceptor_(io_service_, tcp::endpoint(boost::asio::ip::address::from_string(addr), port)),
    concurrency_(concurrency),
    pool_index(0) {
}

void tcp_server::stop() {
    io_service_.stop();
    for(auto& v : io_service_pool) {
        v->stop();
    }
}

boost::asio::io_service& tcp_server::get_one_io_service() {
    pool_index ++;
    if(pool_index >= io_service_pool.size()) pool_index = 0;
    return *io_service_pool[pool_index];
}

void tcp_server::do_accept() {
    boost::asio::io_service& is = get_one_io_service();
    auto conn = new ::moonlight::conn::tcp_conn(is);
    acceptor_.async_accept(conn->socket(), 
    [this, conn, &is] (boost::system::error_code ec) {
        if (!ec) {
            is.post([conn] {
                char buf[100];
                size_t o = conn->read(buf, 100);
                std::cout.write(buf, o); std::cout << "\n";
            });
        } else {
            delete conn;
        }
        do_accept();
    });
}

void tcp_server::run() {
    for (size_t i = 0; i < concurrency_; i ++) {
        io_service_pool.emplace_back(new boost::asio::io_service());
    }
    do_accept();

    std::thread([this] {
        std::cerr << "tcp server start\n";
        io_service_.run();
    }).join();
}

tcp_server::~tcp_server() {
    io_service_pool.clear();
}

};
};