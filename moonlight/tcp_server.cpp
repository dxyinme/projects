#include "tcp_server.h"

#include <thread>

namespace moonlight{
namespace server{

using tcp = boost::asio::ip::tcp;

tcp_session::tcp_session(tcp::socket _socket)
    :socket_(std::move(_socket)) {

}

void tcp_session::start() {
    
}

tcp_session::~tcp_session() {

}

tcp_server::tcp_server(std::string addr, int port, size_t currency)
    : io_service_(), 
    acceptor_(io_service_, tcp::endpoint(boost::asio::ip::address::from_string(addr), port)),
    currency_(currency),
    pool_index(0) {
}

void tcp_server::stop() {
    io_service_.stop();
    for(auto& v : io_service_pool) v -> stop();
}

boost::asio::io_service& tcp_server::select_io_service() {
    pool_index ++;
    if (pool_index >= io_service_pool.size()) {
        pool_index = 0;
    }
    return *io_service_pool[pool_index];
}

void tcp_server::do_accept() {
    boost::asio::io_service& is = select_io_service();
    auto conn_ptr = new ::moonlight::conn::tcp_conn(is);
    acceptor_.async_accept(conn_ptr -> socket(), 
        [this, conn_ptr, &is] (boost::system::error_code ec) {
            if (!ec) {
                is.post([conn_ptr] {
                    std::cerr << "[read OK]";
                    char buf[105];
                    size_t length = conn_ptr->read(buf, 100);
                    std::cerr.write(buf, length);
                    std::cerr << "\n";
                    conn_ptr->write(buf, length);
                    conn_ptr->shutdown();
                    conn_ptr->close();
                });
            } else {
                delete conn_ptr;
            }
            do_accept();
        });
}

void tcp_server::run() {
    for (size_t i=0; i < currency_; i ++) {
        io_service_pool.emplace_back(new boost::asio::io_service());
    }
    for (size_t i=0; i < currency_; i ++) {
        io_service_work_pool.emplace_back(new boost::asio::io_service::work(*io_service_pool[i]));
        th_pool.emplace_back(std::thread([this, i]{
            io_service_pool[i]->run();
        }));
    }
    try {
        do_accept();
        io_service_.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

tcp_server::~tcp_server() {
    stop();
    for(size_t i=0;i<currency_;i++) {
        th_pool[i].join();
    }
    io_service_pool.clear();
}

};
};