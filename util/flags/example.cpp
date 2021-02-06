#include "util/flags/flags.h"

#include <iostream>

int32_t v32 = 0;
int64_t v64 = 123;
bool bo = true, nbo = false;
const char * test_string = "test_string";

int main(int argc, char** argv) {
    namespace fg = util::flags;
    
    fg::clean_flags();
    // register flags
    fg::flag_int32(&v32, "i32", "test i32");
    fg::flag_int64(&v64, "i64", "test i64");
    fg::flag_bool(&bo, "bool", "test bool");
    fg::flag_bool(&nbo, "nbool", "test no bool");
    fg::flag_string(&test_string, "string", "test string");

    fg::parse_commandline(argc,argv);

    std::cout << std::endl;
    std::cout << "v32           = " << v32 << std::endl;
    std::cout << "v64           = " << v64 << std::endl;
    std::cout << "bo            = " << bo  << std::endl;
    std::cout << "nbo           = " << nbo << std::endl;
    std::cout << "test_string   = " << test_string << std::endl;
    std::cout << std::endl;
    return 0;
}