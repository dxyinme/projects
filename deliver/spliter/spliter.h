

namespace deliver {
namespace spliter {

// return how many blocks this filename split out.
// -1 for split failed
int64_t split(const char* filename, std::vector<std::string>& md5);

};
};