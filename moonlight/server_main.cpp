#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <moonlight/server.h>
#include <boost/asio.hpp>

int main(int argc, char** argv) {
    try {
        boost::asio::io_service io_service;
        moonlight::server::RPCServer s(io_service, 18080);
        io_service.run();
    }catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}