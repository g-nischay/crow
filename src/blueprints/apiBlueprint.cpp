#include "handlers.h"
#include "blueprints/apiBP.h"
#include <crow.h>

crow::Blueprint createApiBp(){
    crow::Blueprint apiBp("api");
    
    CROW_BP_ROUTE(apiBp, "/calc/<int>/<int>")([](int a, int b){
        crow::json::wvalue js;
        js["b"] = a;
        js["a"] = b;
        js["+"] = a+b;
        js["-"] = a-b;
        js["*"] = a*b;
        if(b) js["/"] = static_cast<double>(a)/b;

        crow::response res;
        res.set_header("Content-Type", "application/json");
        res.code = 200;
        res.body = js.dump();
        return res;
    });

    CROW_BP_CATCHALL_ROUTE(apiBp)([](const crow::request& req){
        CROW_LOG_INFO<<"[API CATCHALL ] API Catchall for url" + req.url + "\n";
        return crow::response(404,"API Catchall, no route for: " + req.url + "\nRefer to your API usage.\n");
    });

    return apiBp;
}
