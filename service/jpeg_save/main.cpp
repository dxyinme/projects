#include "util/flags/flags.h"

#include <crow/crow.h>

#include <cstring>
#include <vector>
#include <utility>
#include <iostream>

int32_t port = 18080;
const char* dirname = "dir/";

int main(int argc, char** argv) {

    util::flags::flag_int32(&port, "port", "the port this service listen to");
    util::flags::flag_string(&dirname, "dir", "the dir which be used to save the jpeg");
    util::flags::parse_commandline(argc, argv);
    
    crow::SimpleApp app;
    CROW_ROUTE(app, "/upload/img")
    .methods("POST"_method, "GET"_method)
    ([&](const crow::request& req, crow::response& rsp){
        namespace CJ = crow::json;
        CROW_LOG_INFO << req.body;
        CJ::wvalue ret;
        ret["finished"] = true;
        rsp.add_header("Content-Type", "application/json;charset=UTF-8");
        rsp.add_header("Access-Control-Allow-Origin", "*");
        rsp.write(CJ::dump(ret));
        rsp.end();
    });

    app.port(port).multithreaded().run();

    return 0;
}