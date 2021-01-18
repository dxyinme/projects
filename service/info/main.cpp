#include <crow/crow.h>

#include <cstring>

int main() {
    int roc = 1414;
    crow::SimpleApp app;
    CROW_ROUTE(app, "/<string>")([&](std::string x){
        crow::json::wvalue js;
        js["x"] = x;
        js["roc"] = roc;
        return js;
    });
    app.port(18080).multithreaded().run();
    return 0;
}