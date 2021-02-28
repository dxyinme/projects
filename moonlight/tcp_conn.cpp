#include "tcp_conn.h"

namespace moonlight{
namespace conn{

using tcp = boost::asio::ip::tcp;

tcp_conn::tcp_conn(boost::asio::io_service& io_service_) :
    socket_(io_service_) {
    }

size_t tcp_conn::read(char* buf, size_t want_len) {
    try {
        boost::system::error_code error;
        size_t ret = socket_.read_some(boost::asio::buffer(buf, want_len), error);
        if (error == boost::asio::error::eof) {
            return ret;
        } else if (error) {
            throw boost::system::system_error(error); 
        }
        return ret;
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return 0u;
    }
}

tcp::socket& tcp_conn::socket() {
    return socket_;
}

void tcp_conn::write(char* buf, size_t want_len) {
    boost::asio::write(socket_, boost::asio::buffer(buf, want_len));
}

void tcp_conn::close() {
    socket_.close();
}

tcp_conn::~tcp_conn() { }

};
};
