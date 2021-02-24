#include "request.h"

namespace moonlight {
namespace request {


uint32_t bytes_to_u32(uint8_t* ch) { 
    return (uint32_t) ch[0]
        | ((uint32_t) ch[1] << 8)
        | ((uint32_t) ch[2] << 16)
        | ((uint32_t) ch[3] << 24);
}

baseRequest::baseRequest() {
    is_method = true;
}


void baseRequest::reset() {
    method.clear();
    body.clear();
    is_method = true;
}

std::vector<boost::asio::const_buffer> baseRequest::to_buffers() {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(method));
    buffers.push_back(boost::asio::buffer("\r\n"));
    buffers.push_back(boost::asio::buffer(boost::lexical_cast<std::string>(body.size())));
    buffers.push_back(boost::asio::buffer(body));
    return buffers;
}

int baseRequest::parse(char* ch, size_t length) {
    for(size_t i = 0; i < length; i++) {
        if(!is_method) {
            body.push_back(ch[i]);
            continue;
        }
        if(isalpha(ch[i])) {
            method.push_back(ch[i]);
            continue;
        } else if (ch[i] == '\r' && i + 1 < length && ch[i+1] == '\n') {
            i += 2;
            is_method = false;
            if(i + 3 < length) {
                bodyLength = (size_t) bytes_to_u32((uint8_t*) (ch + i));
                i += 3;
                continue;
            } else {
                return parse_bad;
            }
        } else {
            return parse_bad;
        }
    }
    if(body.size() < bodyLength || is_method) return parse_endless;
    return parse_end;
}

baseRequest::~baseRequest() {}


};
};