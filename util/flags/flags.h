#ifndef UTIL_FLAGS_HPP
#define UTIL_FLAGS_HPP
#pragma once

#include "util/string_utils/string_utils.h"

#include <unordered_map>
#include <cstring>
#include <cstdio>
#include <iostream>

/*
usage:
./xxx_bin --param1 value1 --param2 value2 --bool_param1 --no-bool_param2 ...
*/

namespace util {
namespace flags {

enum flag_t {
    FLAG_TYPE_INT32, 
    FLAG_TYPE_INT64, 
    FLAG_TYPE_BOOL, 
    FLAG_TYPE_STRING
};

struct flag_item {
    const char* name;
    const char* help;
    flag_t type;
    void* value;
};

void clean_flags();

int parse_commandline(int argc, char** argv);

void output_flag_help();

void flag_int32(int32_t* item, const char* name, const char* help);

void flag_int64(int64_t* item, const char* name, const char* help);

void flag_bool(bool* item, const char* name, const char* help);

void flag_string(const char** item, const char* name, const char* help);

};
};

#endif