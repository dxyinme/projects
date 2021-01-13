#include "util/dlogger/dlogger.h"

int main() {
    // log init .
    dlogger::init_log("xxxx.log", true);
    int test1 = 1, test2 = 2;
    char o[] = "10242394fdffsdf";
    
    // log as format.
    DLOGF(dlogger::INFO, "%d != %d dlog = %s", test1, test2, o);

    // log as stream.
    std::string ss_test = "hahahah test for it"; 
    for(int i=1;i<=200;i++) {
        DLOG(dlogger::INFO) << "lalala" << ss_test << std::endl;
        if(i == 192) DLOG(dlogger::WARN) << 1111 << " out: "<< i << std::endl;
    }
    // log flush to file.
    dlogger::log_flush();
    return 0;
}