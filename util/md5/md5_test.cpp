#include "util/md5/md5.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>

using namespace util::md5;

int main(int argc , char** argv) {
    uint8_t result[16];
    if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }
    char* msg = argv[1];
    md5_string(msg, result);
    // display result
    for (int i = 0; i < 16; i++) {
        printf("%2.2x", result[i]);
    }
    puts("");
    return 0;
}