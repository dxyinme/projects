#include "flags.h"

namespace util {
namespace flags {

#define VERSION 1.0

#define USAGE "--help for see help \nfor int32_t/int32_t/string , use like --param value is ok\n such as ./bin --v32 1919 --v64 810893\nfor bool , use like --param (for true) --no-param (for false)\n such as ./bin --test_true --no-test_false\n"

std::unordered_map<std::string, flag_item> flag_map;

void clean_flags() { flag_map.clear(); }

bool is_flag(const char* s) {
    return (strlen(s) > 2 && s[0] == '-' && s[1] == '-');
}

bool is_false(const char* s) {
    return strncmp(s, "--no-", 5) == 0;
}

std::string get_arg_name(const char* s, int l) {
    while(s[l] != '-') --l;
    l ++;
    return std::string(s + l);
}

int parse_commandline(int argc, char** argv) {
    int i = 1;
    bool show_help = false;
    flag_bool(&show_help, "help", "output help");
    for( ; i < argc; i++) {
        const char* arg = argv[i];
        int l = strlen(arg);
        if(!is_flag(arg)) {
            std::cerr << "flag parse error";
            exit(-1);
        }
        std::string arg_name_str = get_arg_name(arg, l-1);
        if(flag_map.find(arg_name_str) == flag_map.end()) {
            std::cerr << "no such flag as " << arg_name_str ;
            exit(-1);
        }
        
        flag_item* now_item = &(flag_map[arg_name_str]);
        if(now_item->type == FLAG_TYPE_INT32) {
            if(i + 1 >= argc) {
                std::cerr << "flag parse error" ;
                exit(-1);
            }
            i++;
            int ison = sscanf(argv[i], "%d", (int32_t *) now_item->value);
            if (ison == 0) {
                std::cerr << "flag parse error" ;
                exit(-1);
            }
        } else if (now_item->type == FLAG_TYPE_INT64) {
            if(i + 1 >= argc) {
                std::cerr << "flag parse error" ;
                exit(-1);
            }
            i++;
            int ison = sscanf(argv[i], "%ld", (int64_t *) now_item->value);
            if (ison == 0) {
                std::cerr << "flag parse error" ;
                exit(-1);
            }
        } else if (now_item->type == FLAG_TYPE_BOOL) {
            *(bool *) now_item->value = is_false(arg) ? false : true;
        } else if (now_item->type == FLAG_TYPE_STRING) {
            if(i + 1 >= argc) {
                std::cerr << "flag parse error" ;
                exit(-1);
            }
            i++;
            *(const char ** ) now_item->value = argv[i];
        }
    }
    if (show_help) {
        output_flag_help();
        exit(0);
    }
    return 0;
}

void output_flag_help() {
    
    std::cout << "powered by dxyinme Projects@flags \n\tVERSION = " << VERSION << "\n\n\n";

    std::cout << USAGE << "\n";

    for(auto& it : flag_map) {
        flag_item item = it.second;
        std::cout << "--" << it.first << "\t " << item.help ;
        if(item.type == FLAG_TYPE_STRING) {
            std::cout << " [string] default (\"" << *( const char** ) item.value << "\")";
        } else if (item.type == FLAG_TYPE_INT32) {
            std::cout << " [int32_t] default (" << *(int32_t *) item.value << ")";
        } else if (item.type == FLAG_TYPE_BOOL) {
            std::cout << " [bool] default (";
            if (*(bool *) item.value == true) std::cout << "true";
            else std::cout << "false";
            std::cout << ")";
        } else if (item.type == FLAG_TYPE_INT64) {
            std::cout << " [int64_t] default (" << *(int32_t *) item.value << ")";
        }
        std::cout << std::endl;
    }

    exit(0);
}

void flag_int32(int32_t* item, const char* name, const char* help) { 
    flag_item now;
    now.name = name;
    now.help = help;
    now.value = item;
    now.type = FLAG_TYPE_INT32;
    flag_map[name] = now;    
}

void flag_int64(int64_t* item, const char* name, const char* help) { 
    flag_item now;
    now.name = name;
    now.help = help;
    now.value = item;
    now.type = FLAG_TYPE_INT64;
    flag_map[name] = now;
}

void flag_bool(bool* item, const char* name, const char* help) { 
    flag_item now;
    now.name = name;
    now.help = help;
    now.value = item;
    now.type = FLAG_TYPE_BOOL;
    flag_map[name] = now;
}

void flag_string(const char** item, const char* name, const char* help) { 
    flag_item now;
    now.name = name;
    now.help = help;
    now.value = item;
    now.type = FLAG_TYPE_STRING;
    flag_map[name] = now;
}

};
};