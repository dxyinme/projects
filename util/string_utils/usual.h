#ifndef USUAL_H
#define USUAL_H
#pragma once


#include <cstring>
#include <string>
#include <vector>

namespace util {
namespace string_utils {

// split string s by c
void split(std::string& s, std::string& c, std::vector<std::string>& string_after_split);

std::string merge(std::vector<std::string>& string_wait_for_merge, std::string& c);

};
};

#endif