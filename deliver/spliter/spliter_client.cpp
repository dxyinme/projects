#include "deliver/spliter/spliter.h"

#include <cstring>
#include <cstdio>
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 1) {
        std::cout << "error argc, want bigger than 1 or equal to 1" << std::endl;
        return -1;
    }
    std::string filename = argv[1];
    deliver::spliter::description temp(filename.c_str());
    std::cout << temp.to_string() << std::endl;
    return 0;
}