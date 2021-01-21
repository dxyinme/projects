#include <crow/crow.h>

#include <cstring>
#include <vector>
#include <utility>

int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/info")([](){
        using namespace crow::json;
        using namespace std;
        wvalue ret;
        wvalue pal_obj;
        vector<string> util_list;
        
        util_list.push_back("dlogger");
        util_list.push_back("progress_show");
        util_list.push_back("md5");
        
        pal_obj["util"] = util_list;
        ret["ProjectAndLib"] = move(pal_obj);
        return ret;
    });
    app.port(18080).multithreaded().run();
    return 0;
}