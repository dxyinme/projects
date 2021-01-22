#include "util/md5/md5.h"
#include <cstring>
#include <stdint.h>
#include <cstdio>

// can be used in big file md5 calculating

int main(int argc, char* argv[]) {
    if (argc < 1) {
        return 0;
    }
    uint8_t result[16];
    util::md5::md5_file(argv[1], result, util::md5::MD5_OP::BINARY);
    for(int i=0;i<16;i++) printf("%2.2x", result[i]);
    printf(" %s\n", argv[1]);
    return 0;
}