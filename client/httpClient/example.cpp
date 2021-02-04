#include "client/httpClient/httpClient.h"
#include <mongoose/mongoose.h>

#include <cstring>
#include <iostream>

int main() {
    client::httpClient::http_client _http_client;
    _http_client.s_url = "http://www.dxyinme.xyz";
    _http_client.HTTP_GET();
    if(_http_client.done) {
        std::cout << _http_client.r_body << std::endl;
    }
    _http_client.s_url = "http://localhost:18080/test_json"; // this service from //service/info/main.cpp
    _http_client.s_body = "{\"name\":\"cici\"}";
    _http_client.content_type = "application/json;charset=utf-8";
    _http_client.HTTP_POST();
    if(_http_client.done) {
        std::cout << _http_client.r_body << std::endl;
    }
    return 0;
}