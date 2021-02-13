#include "util/flags/flags.h"

#include <crow/crow.h>

#include <cstring>
#include <vector>
#include <utility>
#include <iostream>

int32_t port = 18080;
const char* dirname = "dir/";
std::string dirname_str = "dir/";

crow::SimpleApp app;

int main(int argc, char** argv) {

    util::flags::flag_int32(&port, "port", "the port this service listen to");
    util::flags::flag_string(&dirname, "dir", "the dir which be used to save the jpeg, please write like `dir/` must with `/`");
    util::flags::parse_commandline(argc, argv);
    
    dirname_str = dirname;

    CROW_ROUTE(app, "/showAll")
    ([&](const crow::request& req, crow::response& rsp){
        // todo
        rsp.add_header("Access-Control-Allow-Origin", "*");
        rsp.write("showAll");
        rsp.end();
    });

    CROW_ROUTE(app, "/upload/img")
    .methods("POST"_method)
    ([&](const crow::multipart::message& req, crow::response& rsp){
        namespace CJ = crow::json;
        CJ::wvalue ret;
        
        FILE* fp = fopen((dirname_str + "haha.jpg").c_str(), "w");
        
        for(size_t i=0;i<req.parts[0].body.size();i++) {
            fputc(req.parts[0].body[i], fp);
        }
        fclose(fp);

        ret["finished"] = true;
        
        rsp.add_header("Content-Type", "application/json;charset=UTF-8");
        rsp.add_header("Access-Control-Allow-Origin", "*");
        rsp.write(CJ::dump(ret));
        rsp.end();
    });

    app.port(port).multithreaded().run();

    return 0;
}