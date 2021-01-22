#include "deliver/spliter/spliter.h"

#include <iostream>
#include <cstdio>

int main() {
    FILE* f = fopen("test_10MB", "w");
    for(int64_t i = 0; i < 1024L * 1024L * 10; i ++) fputs("x", f); 
    fclose(f);
    {
        deliver::spliter::block_manager bm("test_10MB");
        printf("file size = %lld B\n", (long long) bm.get_block_num() * deliver::spliter::EACH_SUB_SIZE);
    }
    deliver::spliter::description temp("test_10MB");
    std::cout << temp.to_string() << std::endl;
    return 0;
}