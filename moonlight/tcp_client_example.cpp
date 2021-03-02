#include "moonlight/tcp_conn.h"

#include <boost/asio.hpp>
#include <memory>

using tcp = boost::asio::ip::tcp;

int main(int argc, char ** argv) {
    boost::asio::io_service io_service;
    auto conn_ptr = std::make_shared<moonlight::conn::tcp_conn>(io_service);
    tcp::resolver resolver(io_service);
    boost::asio::connect(conn_ptr->socket(), resolver.resolve({"0.0.0.0", "18080"}));
    char req[105] = "helloworld";
    conn_ptr->write(req, 11);
    char rsp[105];
    size_t rsp_len = conn_ptr->read(rsp, 100);
    conn_ptr->close();
    std::cout.write(rsp, rsp_len);
    std::cout << "\n";
    // while(1);
    return 0;
}