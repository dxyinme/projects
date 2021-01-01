#include "dlogger.h"

#include <stdarg.h>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <iostream>
#include <mutex>

namespace dlogger{

const int TIME_BUF = 105;
const int LOG_LEVEL_SZ = 5;
const int LOGF_BUF = (1 << 15);
const char* LOG_LEVEL[LOG_LEVEL_SZ] = {
    "[DEBUG]",
    "[INFO]",
    "[WARN]",
    "[ERROR]",
    "[FATAL]"
};

int now_count_log_file;

bool logtostderr;

std::string log_filename_prefix, now_log_filename;

FILE* log_file_stream;

std::mutex file_mu;

void init_log(std::string _log_filename_prefix, bool _logtostderr) {
    logtostderr = logtostderr;
    log_filename_prefix = _log_filename_prefix;
    now_count_log_file = 0;
    now_log_filename = log_filename_prefix + "." + std::to_string(now_count_log_file);
    log_file_stream = fopen(now_log_filename.c_str(), "a");
}

void add_pre_format(std::ostringstream& oss, int level, const char* filename, int line) {
    static char time_str[TIME_BUF];
    static time_t now_time;
    now_time = time(NULL);
    strftime(time_str, TIME_BUF, "%Y-%m-%d %H:%M:%S", localtime(&now_time));
    oss << LOG_LEVEL[level] << "\t[" << time_str << "]" << "\t" << filename << "\tline:" << line << "]\t";
}

void new_log(std::ostringstream& oss, int level, const char* filename, int line) {
    add_pre_format(oss, level, filename, line);
}

std::string logf(int level, const char* filename, int line, const char* format, ...) {
    std::ostringstream oss;
    new_log(oss, level, filename, line);
    static char log_content[LOGF_BUF];
    va_list ap;
    va_start(ap, format);
    vsnprintf(log_content, LOGF_BUF, format, ap);
    va_end(ap);
    oss << log_content;
    return oss.str();
}

void log_to_file(const char* s) {
    file_mu.lock();
    fprintf(log_file_stream, "%s\n", s);
    file_mu.unlock();
}

}