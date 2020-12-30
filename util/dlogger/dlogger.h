#ifndef DLOGGER_H
#define DLOGGER_H
#pragma once

#include <mutex>
#include <memory>

namespace dlogger {

const int DEBUG = 0;
const int INFO = 1;
const int WARN = 2;
const int ERROR = 3;
const int FATAL = 4;

class log {
    
private:

    bool logtostderr;

    std::shared_ptr<std::mutex> mu_ptr;

    FILE* file;

public:

    log(const char* file_name);

    void set_logtostderr(bool v);

    void logf(int level, const char* fmt, ...);

    ~log(){
        if(file != nullptr) {
            fclose(file);
        }
    }

};

}
#endif