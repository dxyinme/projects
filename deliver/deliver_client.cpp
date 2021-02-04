#include "deliver/spliter/spliter.h"
#include "deliver/collector/collector.h"

#include <cstring>
#include <iostream>

deliver::collector::Collector file_collector;

void init() {
    std::string description_string;
    std::cin >> description_string;
    file_collector.initial(description_string);
}

int main(int argc, char** argv) {
    init();
    for(size_t i = 0, j = 0; i < file_collector.get_file_size(); i += deliver::collector::EACH_SUB_SIZE, j ++) {
        char* now_ch = new char[deliver::collector::EACH_SUB_SIZE + 5];
        size_t now_ch_length = deliver::collector::EACH_SUB_SIZE;
        if(now_ch_length > file_collector.get_file_size() - i + 1) {
            now_ch_length = file_collector.get_file_size() - i + 1;
        }
        for(size_t id = 0; id < now_ch_length; id ++) {
            now_ch[id] = 'x';
        }
        file_collector.write_to(now_ch, j);
        delete(now_ch);
    }
    return 0;
}