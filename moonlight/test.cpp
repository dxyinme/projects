#include <bits/stdc++.h>

using namespace std;

uint32_t bytes_to_u32(uint8_t* ch) { 
    return (uint32_t) ch[0]
        | ((uint32_t) ch[1] << 8)
        | ((uint32_t) ch[2] << 16)
        | ((uint32_t) ch[3] << 24);
}

void u32_to_bytes(uint8_t* ch, uint32_t val) {
    ch[0] = (uint8_t) val;
    ch[1] = (uint8_t) (val >> 8);
    ch[2] = (uint8_t) (val >> 16);
    ch[3] = (uint8_t) (val >> 24);
}

int main(){
    char ch[15];
    uint32_t otr = -1, item = 1232489239;
    u32_to_bytes((uint8_t*)(ch+3), item);
    otr = bytes_to_u32((uint8_t*)(ch+3));
    cout << (size_t)otr << endl << item << endl;
    return 0;
}