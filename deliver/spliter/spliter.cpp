#include "spliter.h"

#include <cstdio>

namespace deliver {
namespace spliter {

// reference
// https://zh.cppreference.com/w/cpp/io/c

const int64_t EACH_SUB_SIZE = 128 * 1024; // 128 KB

block_manager::block_manager(const char* filename) {
    f = fopen(filename, "rb");
}

int64_t block_manager::get_block_num() {
    fseek(f, 0L, SEEK_END);
    int64_t file_sz = ftell(f);
    return file_sz;
}

void block_manager::get_block(int64_t block_id, char* block_content) {
    fseek(f, EACH_SUB_SIZE * block_id * sizeof(char), SEEK_END);
    fread(block_content, EACH_SUB_SIZE, 1, f);
}

block_manager::~block_manager() {
    if(f) {
        fclose(f);
    }
}

block_iterator::block_iterator(const char* filename) {
    f = fopen(filename, "rb");
}

void block_iterator::next_block(char* block_content) {
    fread(block_content, EACH_SUB_SIZE, 1, f);
}
block_iterator::~block_iterator() {
    if(f) {
        fclose(f);
    }
}
};
};