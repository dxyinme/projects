#include "util/dlogger/dlogger.h"

int main() {
    dlogger::init_log("xxxx.log", false);
    for(int i=1;i<=(1<<10);i++) {
        DLOGF(dlogger::WARN, "now i = %d : we are test\ncases", i);
    }
    dlogger::log_flush();
    return 0;
}