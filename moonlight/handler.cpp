#include "handler.h"

namespace moonlight{
namespace handler{

using tcp = boost::asio::ip::tcp;

base::base() {

}

void base::handle(::moonlight::conn::tcp_conn* conn_ptr) {
    std::cerr << "[read OK]";
    char buf[105];
    size_t length = conn_ptr->read(buf, 100);
    std::cerr.write(buf, length);
    std::cerr << "\n";
    conn_ptr->write(buf, length);
    conn_ptr->shutdown();
    conn_ptr->close();
}

base::~base() {

}

};
};