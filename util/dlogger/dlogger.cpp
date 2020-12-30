#include "dlogger.h"

#include <stdarg.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace dlogger{

const int LOG_BUFSZ = (1 << 15);
const int TIME_BUFSZ = 105;
const int LOG_LEVEL_SZ = 5;

const char* LOG_LEVEL[LOG_LEVEL_SZ] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};


log::log(const char* file_name) {
    this->logtostderr = false;
    this->mu_ptr = std::make_shared<std::mutex>();
    // read to file as append.
    this->file = fopen(file_name, "a");
}

void log::set_logtostderr(bool v) {
    this->logtostderr = v;
}

void log::logf(int level, const char* fmt, ...) {
    if (level >= LOG_LEVEL_SZ) {
        return ;
    }
    static char time_str[TIME_BUFSZ];
    static time_t time_now = time(NULL);
    // sprintf fmt-time.
    strftime(time_str, TIME_BUFSZ - 1, "%Y-%m-%d %H:%M:%S", localtime(&time_now));

    // sprintf fmt content.
    va_list ap;
    static char logs[LOG_BUFSZ];
    va_start(ap, fmt);
    vsnprintf(logs, LOG_BUFSZ - 1, fmt, ap);
    va_end(ap);
    this->mu_ptr->lock();
    if(this->file != nullptr) {    
        fprintf(this->file, "[%s]\t[%s]\t%s\n", LOG_LEVEL[level], time_str, logs);
    }

    if(this->logtostderr) {
        printf("[%s]\t[%s]\t%s\n", LOG_LEVEL[level], time_str, logs);
    }
    this->mu_ptr->unlock();
    if (level == LOG_LEVEL_SZ - 1) {
        // is Fatal
        exit(-1);
    }
}

}