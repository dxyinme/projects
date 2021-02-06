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

        return ret;
    });
    app.port(18080).multithreaded().run();
    return 0;
}