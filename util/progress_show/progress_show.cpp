#include "progress_show.h"

#include <cstdio>

namespace progress_show {

const int RATE_SHOW_SIZE = 10;

base::base(int64_t _sum_size) {
    sum_size = _sum_size;
    now_size = 0LL;
}

void base::begin() {
    flush();
}

void base::update_now_size(int64_t _now_size) {
    mu.lock();
    now_size = _now_size;
    if(now_size >= sum_size) now_size = sum_size;
    flush();
    mu.unlock();
}

void base::inc_now_size(int64_t delta) {
    mu.lock();
    now_size += delta;
    if(now_size >= sum_size) now_size = sum_size;
    flush();
    mu.unlock();
}

void base::flush() {
    for(int i = 1; i <= RATE_SHOW_SIZE; i ++) fprintf(stderr, "\b");
    double now_rate = 1.0 * now_size / sum_size;
    fprintf(stderr, "[%6.2f%%]", now_rate * 100);
    if(now_size == sum_size) fprintf(stderr, "\n\r");
}

};