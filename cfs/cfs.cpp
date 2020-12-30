#include "util/dlogger/dlogger.h"

dlogger::log logger = dlogger::log("log.txt");

int main() {
    logger.set_logtostderr(true);

    logger.logf(dlogger::DEBUG, "xxx %d %s, %f", 1999, "xxxxxcqqq", 3.14);

    logger.logf(dlogger::ERROR, "xxx %d %s, %f", 1999, "xxxxxcqqq", 3.14);

    logger.logf(dlogger::INFO, "xxx %d %s, %f", 1999, "xxxxxcqqq", 3.14);
    logger.logf(dlogger::WARN, "xxx %d %s, %f", 1999, "xxxxxcqqq", 3.14);
    logger.logf(dlogger::FATAL, "xxx %d %s, %f", 1999, "xxxxxcqqq", 3.14);
    logger.logf(dlogger::WARN, "xxx %d %s, %f", 1999, "xxxxxcqqq", 3.14);
    return 0;
}