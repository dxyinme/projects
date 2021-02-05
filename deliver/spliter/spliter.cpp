#include "spliter.h"

#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <vector>
#include <iostream>

namespace deliver {
namespace spliter {

// reference
// https://zh.cppreference.com/w/cpp/io/c

block_manager::block_manager(const char* filename) {
    f = fopen(filename, "rb");
}

size_t block_manager::get_block_num() {
    size_t file_sz = get_file_size();
    size_t block_num = file_sz / EACH_SUB_SIZE;
    if(file_sz % EACH_SUB_SIZE != 0) {
        block_num ++;
    }
    return block_num;
}

size_t block_manager::get_file_size() {
    fseek(f, 0L, SEEK_END);
    return ftell(f);
}

void block_manager::get_block(size_t block_id, char* block_content) {
    fseek(f, EACH_SUB_SIZE * block_id * sizeof(char), SEEK_SET);
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
    // filename = _filename;
    {
        block_manager bm(_filename);
        block_number = bm.get_block_num();
        file_size = bm.get_file_size();
    }
    using namespace util::md5;
    std::string full_filename = _filename;
    std::string split_item = "/";
    std::vector<std::string> spliter_vec;
    util::string_utils::split(full_filename, split_item, spliter_vec);
    filename = (*--spliter_vec.end());
    md5_string(filename.c_str(), filenameMD5);
    md5_file(_filename, fileMD5, BINARY); 
}

std::string description::to_string() {
    std::stringstream ss(""); 
    char md5_body[32];
    for(size_t i = 0 ; i < 16; i++) {
        sprintf(md5_body + i * 2, "%2.2x", filenameMD5[i]);
    }
    ss << "FILENAME=" << filename << "|" << "NAME=" << md5_body << "|FILE=";
    for(size_t i = 0 ; i < 16; i++) {
        sprintf(md5_body + i * 2, "%2.2x", fileMD5[i]);
    }
    ss << md5_body << "|BLOCKNUM=" << block_number;
    ss << "|FILE_SIZE=" << file_size;
    return ss.str();
}

description::~description() {

}

};
};