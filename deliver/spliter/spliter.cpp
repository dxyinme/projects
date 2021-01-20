#include "spliter.h"

#include <cstdio>

namespace deliver {
namespace spliter {

const int EACH_SUB_SIZE = 128 * 1024; // 128 KB

int64_t split(const char* filename, std::vector<std::string>& md5);

};
};