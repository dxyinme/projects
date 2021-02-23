#include "handler.h"

namespace moonlight {
namespace handler {

handler::handler() {}

void handler::handle(const ::moonlight::request::baseRequest& base_request_, 
    ::moonlight::response::baseResponse& base_response_) {
    base_response_.method = base_request_.method;
    base_response_.body = base_request_.body;
}

handler::~handler() {}

};
};
