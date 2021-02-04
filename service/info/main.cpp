#include <crow/crow.h>

#include <cstring>
#include <vector>
#include <utility>
#include <iostream>

int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/info")([](){
        using namespace crow::json;
        using namespace std;

        wvalue ret, pal_obj;
        vector<string> util_list;
        
        util_list.push_back("dlogger");
        util_list.push_back("progress_show");
        util_list.push_back("md5");
        
        pal_obj["util"] = util_list;
        ret["ProjectAndLib"] = std::move(pal_obj);
        return ret;
    });

    CROW_ROUTE(app, "/test_json")
    .methods("POST"_method)
    ([](const crow::request& req){
        using namespace std;
        crow::json::wvalue ret;
        auto x = crow::json::load(req.body);
        std::cout << req.body << std::endl;
        if (!x) {
            return crow::response(400);
        }
        ret = std::move(x);
        ret["status"] = "finish";
        std::string s = crow::json::dump(ret);
        return crow::response{ s };
    });

    app.port(18080).multithreaded().run();
    return 0;
}