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

template <typename... Types>
std::string log(int level, const char* filename, int line, const Types&... args) {
    std::ostringstream oss;
    new_log(oss, level, filename, line);
    std::initializer_list <int> { ( [&] { oss << args << " "; }(), 0)... };
    return oss.str();
}

std::string logf(int level, const char* filename, int line, const char* format, ...);

void log_to_file(const char* s);

void log_flush();

};
// LEVEL must be suitable in such correspondence :
//  [DEBUG, INFO, WARN, ERROR, FATAL] ----> [0, 1, 2, 3, 4, 5]

#define DLOG(LEVEL,x...) do { std::string dlogger_now_msg = dlogger::log(LEVEL, __FILE__, __LINE__, ##x); \
                                if(dlogger::is_logtostderr())std::cerr << dlogger_now_msg << std::endl; \
                                dlogger::log_to_file(dlogger_now_msg.c_str()); \
                            } while(0)

#define DLOGF(LEVEL,x...) do { std::string dlogger_now_msg = dlogger::logf(LEVEL, __FILE__, __LINE__, ##x); \
                                if(dlogger::is_logtostderr())std::cerr << dlogger_now_msg << std::endl; \
                                dlogger::log_to_file(dlogger_now_msg.c_str()); \
                            } while(0)

#endif