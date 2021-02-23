#include "response.h"

namespace moonlight {
namespace response {

void u32_to_bytes(uint8_t* ch, uint32_t val) {
    ch[0] = (uint8_t) val;
    ch[1] = (uint8_t) (val >> 8);
    ch[2] = (uint8_t) (val >> 16);
    ch[3] = (uint8_t) (val >> 24);
}

baseResponse::baseResponse() {}

std::vector<boost::asio::const_buffer> baseResponse::to_buffers() {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(method));
    buffers.push_back(boost::asio::buffer("\r\n"));
    buffers.push_back(boost::asio::buffer(boost::lexical_cast<std::string>(body.size())));
    buffers.push_back(boost::asio::buffer(body));
    return buffers;
}

baseResponse::~baseResponse() {}

};
};
