#include "moonlight/tcp_server.h"
#include <iostream>
#include "util/flags/flags.h"

int32_t port = 18080;
const char * addr = "0.0.0.0";
int32_t con = 5;

int main(int argc, char ** argv) {
    namespace fg = util::flags;
    fg::clean_flags();
    fg::flag_int32(&port, "port", "listen port");
    fg::flag_string(&addr, "addr", "listen addr");
    fg::flag_int32(&con, "con", "the number of workers");
    fg::parse_commandline(argc, argv);

    moonlight::server::tcp_server s(std::string(addr), (int) port, (size_t) con);
    s.run();
    return 0;
}