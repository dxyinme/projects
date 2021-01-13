#ifndef DLOGGER_H
#define DLOGGER_H
#pragma once

#include <sstream>
#include <iostream>

namespace dlogger {

const int DEBUG = 0;
const int INFO = 1;
const int WARN = 2;
const int ERROR = 3;
const int FATAL = 4;

void init_log(std::string _log_filename_prefix, bool _logtostderr);

bool is_logtostderr();

void new_log(std::ostringstream& oss, int level, const char* filename, int line);

void log_to_file(const char* s);

void log_flush();

class dlog_stream {
private:
    std::ostringstream dlog_stream_oss;
    int self_level;
public:
    dlog_stream(int level, const char* filename, int line) {
        self_level = level;
        new_log(dlog_stream_oss, level, filename, line);
    }

    template<typename T>
    dlog_stream& operator<<(const T& t) {
        dlog_stream_oss << t;
        return *this;
    }
    // get std::endl for end of this log.
    dlog_stream& operator<<(std::ostream& (*)(std::ostream&)) {
        std::string now_log_things = dlog_stream_oss.str();
        if(is_logtostderr()) std::cerr << now_log_things << std::endl;
        log_to_file(now_log_things.c_str());
        // higher than [INFO]
        if(self_level > 1) log_flush();
        return *this;
    }
};

std::string logf(int level, const char* filename, int line, const char* format, ...);

};
// LEVEL must be suitable in such correspondence :
//  [DEBUG, INFO, WARN, ERROR, FATAL] ----> [0, 1, 2, 3, 4]

#define DLOGF(LEVEL,x...) do { std::string dlogger_now_msg = dlogger::logf(LEVEL, __FILE__, __LINE__, ##x); \
                                if(dlogger::is_logtostderr())std::cerr << dlogger_now_msg << std::endl; \
                                dlogger::log_to_file(dlogger_now_msg.c_str()); \
                                if(LEVEL > 1) dlogger::log_flush(); \
                            } while(0)

#define DLOG(LEVEL) dlogger::dlog_stream(LEVEL,__FILE__,__LINE__) 

#endif