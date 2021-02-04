#ifndef COLLECTOR_H
#define COLLECTOR_H
#pragma once

#include "util/string_utils/string_utils.h"

#include <cstring>
#include <cstdio>
#include <vector>
#include <unordered_set>

namespace deliver {
namespace collector {

// equal to deliver::spliter::EACH_SUB_SIZE
const int64_t EACH_SUB_SIZE = 128 * 1024; // 128 KB

class Collector {
private:
    
    size_t file_size;

    std::string filename;

    std::vector<std::string> description_vec;

    std::unordered_set<size_t> waiting_for;

    FILE* fp;

public:
    Collector(std::string _description_string = "");

    void initial(std::string _description_string);

    int write_to(char* content, size_t block_id);

    size_t get_file_size();
    
    ~Collector();
};

};
};

#endif