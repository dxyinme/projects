#include "util/flags/flags.h"
#include "util/md5/md5.h"

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

    CROW_ROUTE(app, "/imgPool/<string>")
    ([&](const crow::request& req, crow::response& rsp, const std::string& img_name) {
        rsp.set_static_file_info(dirname_str + img_name);
        rsp.end();
    });

    CROW_ROUTE(app, "/upload/img")
    .methods("POST"_method)
    ([&](const crow::multipart::message& req, crow::response& rsp){
        namespace CJ = crow::json;
        CJ::wvalue ret;
        
        if(req.parts.size() == 0) {
            ret["errorMsg"] = "upload file failed";
            rsp.write(CJ::dump(ret));
            rsp.end();
            return ;
        }

        // get md5
        util::md5::md5_worker mworker;
        mworker.update((uint8_t *) req.parts[0].body.c_str(), req.parts[0].body.size(), true);

        char md5_str[32 + 4];
        uint8_t* md5_res = new uint8_t[16];

        mworker.get_digest(md5_res);
        for(int i = 0; i < 16; i ++) {
            sprintf(md5_str + (i * 2), "%2.2x", md5_res[i]);
        }
        delete(md5_res);
        md5_str[32] = '\0';
        std::string filename_str = std::string(md5_str);
        filename_str += ".jpg";
        // save file
        FILE* fp = fopen((dirname_str + filename_str).c_str(), "w");
        
        for(size_t i=0;i<req.parts[0].body.size();i++) {
            fputc(req.parts[0].body[i], fp);
        }
        fclose(fp);

        ret["finished"] = true;
        ret["imgSubUrl"] = "/imgPool/" + filename_str;
        
        rsp.add_header("Content-Type", "application/json;charset=UTF-8");
        rsp.add_header("Access-Control-Allow-Origin", "*");
        rsp.write(CJ::dump(ret));
        rsp.end();
    });

    app.port(port).multithreaded().run();

    return 0;
}