#include "dlogger.h"

#include <stdarg.h>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <iostream>
#include <mutex>
#include <iomanip>

namespace dlogger{

const int TIME_BUF = 105;
const int LOG_LEVEL_SZ = 5;
const int LOGF_BUF = (1 << 15);
const int LOG_FILE_BUF = (1 << 12);

const char* LOG_LEVEL[LOG_LEVEL_SZ] = {
    "[DEBUG]",
    "[INFO]",
    "[WARN]",
    "[ERROR]",
    "[FATAL]"
};

int now_count_log_file, log_file_buf_stand;

bool logtostderr;

std::stringstream log_filename_ss;
std::string log_filename_prefix, now_log_filename;

FILE* log_file_stream;

std::mutex file_mu;

static char buffer[LOG_FILE_BUF + 15];

bool is_logtostderr() {
    return logtostderr;
}

void init_log(std::string _log_filename_prefix, bool _logtostderr) {
    logtostderr = logtostderr;
    log_filename_prefix = _log_filename_prefix;
    log_filename_ss.str("");
    std::time_t now_time;
    now_time = std::time(nullptr);
    log_filename_ss << log_filename_prefix << "." << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    now_log_filename = log_filename_ss.str();
    std::cout << now_log_filename << std::endl;
    log_file_stream = fopen(now_log_filename.c_str(), "a");
    log_file_buf_stand = 0;
}

void add_pre_format(std::ostringstream& oss, int level, const char* filename, int line) {
    std::time_t now_time;
    now_time = std::time(nullptr);
    oss << LOG_LEVEL[level] << "\t[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << "]" << "\t" << filename << "\tline:" << line << "]\t";
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

void log_to_file_flush(const char* s) {
    fprintf(log_file_stream, "%s", s);
}

void log_to_file(const char* s) {
    int i;
    file_mu.lock();
    for(i = 0; s[i] != '\0'; i ++) {
        if(s[i] == '\n' || s[i] == '\r') {
            buffer[log_file_buf_stand ++] = '\\';
            buffer[log_file_buf_stand ++] = 'n';
        } else {
            buffer[log_file_buf_stand ++] = s[i];    
        }
        if(log_file_buf_stand >= LOG_FILE_BUF) {
            buffer[log_file_buf_stand] = '\0';
            log_to_file_flush(buffer);
            log_file_buf_stand = 0;
        }
    }
    buffer[log_file_buf_stand ++] = '\n';
    file_mu.unlock();
}

void log_flush() {
    file_mu.lock();
    buffer[log_file_buf_stand] = '\0';
    log_to_file_flush(buffer);
    file_mu.unlock();
}

}