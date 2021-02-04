#include "collector.h"

#include <sstream>
#include <cstring>
#include <iostream>
#include <cstdio>

namespace deliver {
namespace collector {

int fill_file(size_t file_size, FILE* fp) {
    if(fp == nullptr) {
        return -1;
    }
    for(size_t i=0;i<file_size;i++) {
        fputc(' ', fp);
    }
    return 0;
}

Collector::Collector(std::string _description_string) {
    initial(_description_string);
}

void Collector::initial(std::string _description_string) {
    if (_description_string == "") {
        return ;
    }
    description_vec.clear();
    waiting_for.clear();
    std::string split_item = "|";
    util::string_utils::split(_description_string, split_item, description_vec);

    if (description_vec[0].find("FILENAME=") != description_vec[0].npos) 
        description_vec[0] = description_vec[0].replace(description_vec[0].find("FILENAME="), 9, "");

    if (description_vec[1].find("NAME=") != description_vec[1].npos)
        description_vec[1] = description_vec[1].replace(description_vec[1].find("NAME="), 5, "");
    
    if (description_vec[2].find("FILE=") != description_vec[2].npos)
        description_vec[2] = description_vec[2].replace(description_vec[2].find("FILE="), 5, "");
    
    if (description_vec[3].find("BLOCKNUM=") != description_vec[3].npos)
        description_vec[3] = description_vec[3].replace(description_vec[3].find("BLOCKNUM="), 9, "");
    
    if (description_vec[4].find("FILE_SIZE=") != description_vec[4].npos)
        description_vec[4] = description_vec[4].replace(description_vec[4].find("FILE_SIZE="), 10, "");

    std::stringstream ss("");
    ss << description_vec[4];
    ss >> file_size;
    size_t block_num;
    // clear the stringstream
    ss.clear();
    ss.str("");
    ss << description_vec[3];
    ss >> block_num;
    for(size_t i = 0; i < block_num; i++) {
        waiting_for.insert(i);
    }
    fp = fopen(description_vec[0].c_str(), "wb");
    fill_file(file_size, fp);
}

int Collector::write_to(char* content, size_t block_id) {
    fseek(fp, EACH_SUB_SIZE * block_id * sizeof(char), SEEK_SET);
    waiting_for.erase(block_id);
    return fwrite(content, strlen(content), 1, fp);
}

size_t Collector::get_file_size() {
    return file_size;
}

Collector::~Collector() { 
    fclose(fp);
}

};
};