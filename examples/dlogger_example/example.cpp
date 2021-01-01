#include "util/dlogger/dlogger.h"

int main() {
    dlogger::init_log("xxxx.log", true);
    DLOG(dlogger::INFO, 1,2,3,4,"ccc", "INFO");
    DLOGF(dlogger::DEBUG, "t1=%d,t2=%d,s1=%s", 108, 1, "debug");
    DLOGF(dlogger::WARN, "t1=%d,t2=%d,s1=%s", 101, 103, "warn");
    DLOGF(dlogger::ERROR, "t1=%d,t2=%d,s1=%s", 2333, 1023, "error");
    return 0;
}