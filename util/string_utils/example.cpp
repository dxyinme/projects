#include "util/string_utils/string_utils.h"

#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    std::string s, c;
    std::cin >> s >> c;
    std::vector<std::string> vec;
    util::string_utils::split(s, c, vec);
    std::cout << "split:" << std::endl;
    for(auto& val : vec) {
        std::cout << val << std::endl;
    }
    std::cout << "merge:" << util::string_utils::merge(vec, c) << std::endl;
    return 0;
}