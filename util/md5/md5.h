#include <stdint.h>
#include <cstdlib>
namespace util{
namespace md5{

void md5(const uint8_t* initial_msg, size_t initial_len, uint8_t* digest);

void md5_string(char* msg, uint8_t* digest);

};
};