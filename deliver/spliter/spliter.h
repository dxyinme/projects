#include <cstdio>
#include <cstring>
#include <stdint.h>

namespace deliver {
namespace spliter {

class block_manager {
private:

    FILE* f;

public:
    
    block_manager(const char* filename);
    
    int64_t get_block_num();

    // only be used in normal type
    // block_id counted from zero.
    // confirm block_content size bigger than 128 * 1024
    void get_block(int64_t block_id, char* block_content);

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

    int64_t block_number;
public:
    description(const char* _filename);
    
    void get_result(char* result);
    
    ~description();
}

};
};