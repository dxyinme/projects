#include "util/progress_show/progress_show.h"

#include <unistd.h>
#include <thread>
#include <functional>

progress_show::base bar(5000);

void f(int64_t v,int t){
    sleep(t);
    bar.inc_now_size(v);
}

int main() {
    bar.begin();
    int64_t v_vec[] = {100, 200, 3000, 1188, 400, 112};
    int t_vec[] = {2, 5, 3, 30, 11, 29};
    const int vec_len = 6;
    std::thread th_vec[vec_len];
    for(int i=0;i<vec_len;i++) {
        th_vec[i] = std::thread(f, v_vec[i], t_vec[i]);
    }
    for(int i=0;i<vec_len;i++) {
        th_vec[i].join();
    }
    return 0;
}