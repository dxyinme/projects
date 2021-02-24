#include "client.h"

namespace moonlight {
namespace client {

using tcp = boost::asio::ip::tcp;

RPCClient::RPCClient(tcp::socket _socket):
    socket_(std::move(_socket)) {}

void RPCClient::Call(::moonlight::request::baseRequest& request_, 
    ::moonlight::response::baseResponse& response_) {
    mu_.lock();
    boost::asio::write(socket_, request_.to_buffers());
    mu_.unlock();
}

void RPCClient::Close() {

}

RPCClient::~RPCClient() {}

};
};
