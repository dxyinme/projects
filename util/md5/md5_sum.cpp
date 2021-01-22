#include "util/md5/md5.h"
#include <cstring>
#include <stdint.h>
#include <cstdio>

// can be used in big file md5 calculating

int min(size_t A, size_t B) {return A < B ? A : B;}

int main(int argc, char* argv[]) {
    if (argc < 1) {
        return 0;
    }
    FILE* f = fopen(argv[1], "rb");
    fseek(f, 0LL, SEEK_END);
    size_t sz = ftell(f);
    char* fcon = new char[(512 / 8) * 2 + 5];
    fseek(f, 0LL, SEEK_SET);
    uint8_t result[16];
    size_t offset = 0;

    util::md5::md5_worker md5Worker;
    while(offset < sz) {
        size_t now_read_size = min((size_t) 512 / 8, sz - offset);
        fread(fcon, now_read_size, 1, f);
        if(offset + (512 / 8) >= sz) { // end of string
            md5Worker.update((uint8_t *) fcon, now_read_size, true);
            break;
        } else {
            md5Worker.update((uint8_t *) fcon, now_read_size, false);
        }
        offset += now_read_size;
    }

    fclose(f);
    
    md5Worker.get_digest(result);
    for(int i=0;i<16;i++) printf("%2.2x", result[i]);
    printf(" %s\n", argv[1]);
    return 0;
}