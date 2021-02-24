#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <boost/asio.hpp>

#include "moonlight/common.h"

using tcp = boost::asio::ip::tcp;

const int max_length = 65536;
char request[max_length], reply[max_length];

void u32_to_bytes(uint8_t* ch, uint32_t val) {
    ch[0] = (uint8_t) val;
    ch[1] = (uint8_t) (val >> 8);
    ch[2] = (uint8_t) (val >> 16);
    ch[3] = (uint8_t) (val >> 24);
}

int main(int argc , char** argv) {
    try
    {
        boost::asio::io_service io_service;
        tcp::socket s(io_service);
        tcp::resolver resolver(io_service);
        boost::asio::connect(s, resolver.resolve({"0.0.0.0", "18080"}));
        // std::cout << "Enter message: ";
        for (int t = 0 ; t < 3; t ++) {
            memcpy(request, "echo\r\n", 6);
            u32_to_bytes((uint8_t*) (request + 6), 500);
            for(int i=10; i < 500 + 10; i ++) {
                request[i] = 'x';
            }
            request[500 + 10] = '\0';
            // std::cin.getline(request, max_length);
            size_t request_length = 510;
            std::cerr << request_length << std::endl;
            boost::asio::write(s, boost::asio::buffer(request, request_length));
            size_t reply_length = s.read_some(boost::asio::buffer(reply, max_length));
            std::cout << "reply length : " << reply_length << "\n";
        }
        int pause_;
        std::cout << "system pause, input a number:" ;
        std::cin >> pause_;
        request[0] = (char) ::moonlight::common::FIN ;
        request[1] = '\0';
        boost::asio::write(s, boost::asio::buffer(request, 1));
        // std::cout << "Reply is: ";
        // std::cout.write(reply, reply_length);
        // std::cout << "\n";
        while(true);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

}