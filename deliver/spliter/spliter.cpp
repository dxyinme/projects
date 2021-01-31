#include "spliter.h"

#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <iostream>

namespace deliver {
namespace spliter {

// reference
// https://zh.cppreference.com/w/cpp/io/c

block_manager::block_manager(const char* filename) {
    f = fopen(filename, "rb");
}

int64_t block_manager::get_block_num() {
    fseek(f, 0L, SEEK_END);
    int64_t file_sz = ftell(f);
    int64_t block_num = file_sz / EACH_SUB_SIZE;
    if(file_sz % EACH_SUB_SIZE != 0) {
        block_num ++;
    }
    return block_num;
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

description::description(const char* _filename) {
    filename = _filename;
    {
        block_manager bm(_filename);
        block_number = bm.get_block_num();
    }
    using namespace util::md5;
    md5_string(_filename, filenameMD5);
    md5_file(_filename, fileMD5, BINARY); 
}

std::string description::to_string() {
    std::stringstream ss(""); 
    char md5_body[32];
    for(size_t i = 0 ; i < 16; i++) {
        sprintf(md5_body + i * 2, "%2.2x", filenameMD5[i]);
    }
    ss << "NAME=" << md5_body << "|FILE=";
    for(size_t i = 0 ; i < 16; i++) {
        sprintf(md5_body + i * 2, "%2.2x", fileMD5[i]);
    }
    ss << md5_body << "|BLOCKNUM=" << block_number;
    return ss.str();
}

description::~description() {

}

};
};