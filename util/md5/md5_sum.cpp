#include "util/md5/md5.h"
#include <cstring>
#include <stdint.h>
#include <cstdio>

int main(int argc, char* argv[]) {
    if (argc < 1) {
        return 0;
    }
    FILE* f = fopen(argv[1], "rb");
    fseek(f, 0L, SEEK_END);
    int64_t sz = ftell(f);
    char* fcon = new char[sz + 5];
    fseek(f, 0L, SEEK_SET);
    fread(fcon, sz, 1, f);
    fclose(f);
    uint8_t result[16];
    util::md5::md5_string(fcon, result);
    for(int i=0;i<16;i++) printf("%2.2x", result[i]);
    printf(" %s\n", argv[1]);
    return 0;
}