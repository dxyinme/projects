#ifndef SPLITER_H
#define SPLITER_H
#pragma once

#include "util/md5/md5.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <stdint.h>

namespace deliver {
namespace spliter {

const int64_t EACH_SUB_SIZE = 128 * 1024; // 128 KB

class block_manager {
private:

    FILE* f;

public:
    
    block_manager(const char* filename);
    
    size_t get_block_num();

    // only be used in normal type
    // block_id counted from zero.
    // confirm block_content size bigger than 128 * 1024
    void get_block(int64_t block_id, char* block_content);

    size_t get_file_size();

    ~block_manager();
};

class block_iterator {
private:

    FILE* f;

public:
    
    block_iterator(const char* filename);

    void next_block(char* block_content);

    ~block_iterator();
};

class description {
private:
    std::string filename;

    uint8_t fileMD5[16];

    uint8_t filenameMD5[16];

    size_t block_number;

    size_t file_size;
public:
    description(const char* _filename);
    
    std::string to_string();
    
    ~description();
};

};
};

#endif