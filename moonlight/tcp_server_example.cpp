#include "moonlight/tcp_server.h"
#include <iostream>

int main(int argc, char ** argv) {
    moonlight::server::tcp_server s("0.0.0.0", 18080, 5);
    s.run();
    return 0;
}