#ifndef PROGRESS_SHOW_H
#define PROGRESS_SHOW_H
#pragma once

#include <mutex>

namespace progress_show {

class base {
// show as : [38.22%]
private:
    
    int64_t sum_size, now_size;
    
    std::mutex mu;

    // flush to stderr
    void flush();

public:
    base(int64_t _sum_size);

    void begin();

    void update_now_size(int64_t _now_size);

    void inc_now_size(int64_t delta);
    
    ~base() {}
};

};

#endif