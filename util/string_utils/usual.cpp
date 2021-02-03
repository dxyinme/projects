#include "usual.h"

#include <vector>
#include <cstring>
#include <string>
#include <iostream>

namespace util {
namespace string_utils {

void split(std::string& s, std::string& c, std::vector<std::string>& string_after_split) {
    std::string s_now = "";
    for(size_t i=0; i < s.size(); i++) {
        s_now.push_back(s[i]);
        if(s_now.size() >= c.size()) {
            if(s_now.substr(s_now.size() - c.size(), c.size()) == c) {
                string_after_split.push_back(s_now.substr(0, s_now.size() - c.size()));
                s_now = "";
            }
        }
    }
    if(s_now.size() != 0) string_after_split.push_back(s_now);
}

std::string merge(std::vector<std::string>& string_wait_for_merge, std::string& c) {
    std::string s = "";
    for(size_t i = 0;i + 1 < string_wait_for_merge.size();i++) {
        s += string_wait_for_merge[i];
        s += c;
    }
    if(string_wait_for_merge.size() > 0) {
        s += *--string_wait_for_merge.end();
    }
    return s;
}

};
};