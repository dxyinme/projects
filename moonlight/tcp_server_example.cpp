#include "moonlight/tcp_server.h"
#include <iostream>
#include "util/flags/flags.h"

int32_t concurrency = 5;
int32_t port = 18080;
const char * addr = "0.0.0.0";

int main(int argc, char ** argv) {
    namespace fg = util::flags;
    fg::clean_flags();
    fg::flag_int32(&port, "port", "listen port");
    fg::flag_int32(&concurrency, "con", "number of io_service");
    fg::flag_string(&addr, "addr", "listen addr");
    fg::parse_commandline(argc, argv);

    moonlight::server::tcp_server s(std::string(addr), (int) port , (size_t) concurrency);
    s.run();
    return 0;
}