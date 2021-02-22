#include "server.h"

namespace moonlight {
namespace server {

using tcp = boost::asio::ip::tcp;

RPCServer::RPCServer(boost::asio::io_service& io_service, int port) 
    :acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) ,
     socket_(io_service) ,
     conn_pool_() {
        do_accept();
}

void RPCServer::do_accept() {
    acceptor_.async_accept(socket_, 
        [this](boost::system::error_code ec){
            if(!ec) {
                conn_pool_.add( 
                    std::make_shared<conn>( std::move(socket_), conn_pool_ )
                );
            }
            do_accept();
        });
}

RPCServer::~RPCServer() {}

};
};