#include <stdint.h>
#include <cstdlib>
namespace util{
namespace md5{

void md5_string(char* msg, uint8_t* result);


// prepare for large file.
class md5_worker {
private:
    uint8_t* digest;
    uint32_t h0, h1, h2, h3;
    size_t current_size, new_size;
    bool isend;
public:
    // sum_size_ = len(`string`) % pow(2, 64)
    md5_worker();
    // confirm now_len <= 512
    void update(const uint8_t* now_msg, size_t now_len, bool is_end);
    void get_digest(uint8_t* result);
    ~md5_worker();
};

};
};