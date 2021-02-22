#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <boost/asio.hpp>

using tcp = boost::asio::ip::tcp;

const int max_length = 65536;
char request[max_length];

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
        memcpy(request, "echo\r\n", 6);
        u32_to_bytes((uint8_t*) (request + 6), 50000);
        for(int i=10; i < 50000 + 10; i ++) {
            request[i] = 'x';
        }
        request[50000 + 10] = '\0';
        // std::cin.getline(request, max_length);
        size_t request_length = 50010;
        std::cerr << request_length << std::endl;
        boost::asio::write(s, boost::asio::buffer(request, request_length));
        // char reply[max_length];
        // size_t reply_length = s.read_some(boost::asio::buffer(reply, max_length));
        // std::cout << "Reply is: ";
        // std::cout.write(reply, reply_length);
        // std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

}