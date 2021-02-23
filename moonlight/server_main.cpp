#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <moonlight/server.h>
#include <boost/asio.hpp>

int main(int argc, char** argv) {
    boost::asio::io_service io_service;
    moonlight::server::RPCServer s(io_service, 18080);
    s.run();
    return 0;
}