#include "middleware.h"
#include "crowTools.h"
#include "handlers.h"
#include "blueprints/apiBP.h"      //API Blueprint
#include <crow.h>
#include <string>
#include <random>
#include <chrono>

int main(){

    std::mt19937_64 mt{static_cast<std::mt19937::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())};

    crow::App<AdminGuard> app;
    app.loglevel(crow::LogLevel::DEBUG);

//Registering API Blueprint
    crow::Blueprint ApiBp = createApiBp();
    app.register_blueprint(ApiBp);
    
//Default Case
    CROW_ROUTE(app, "/")([&mt](){
        return homeHandle(mt);
    });

//Home Case
    CROW_ROUTE(app, "/home")([&mt](){
        return homeHandle(mt);
    });

//Default Upload Case
    CROW_ROUTE(app, "/upload").methods(crow::HTTPMethod::GET)([](){
        return "Access this page from HomePage";
    });

//Upload Case
    CROW_ROUTE(app, "/upload").methods(crow::HTTPMethod::POST)([](const crow::request& req){
        return uploadHandle(req);
    });

//Hello Case
    CROW_ROUTE(app, "/hello/<string>")([](std::string a){
        return "Hello " + a + "!\n";
    });

//Data Case
    CROW_ROUTE(app, "/data")([](){
        crow::json::wvalue wval;
        wval["status"] = "ok";
        wval["values"] = crow::json::wvalue::list({1,2,3,4,5,6,7,8,9,0});
        return wval;
    });

//Search Case
    CROW_ROUTE(app, "/search")([](const crow::request& req){
        return searchHandle(req);
    });

//Info Case
    CROW_ROUTE(app, "/info")([](const crow::request& req){
        CROW_LOG_DEBUG<<"Someone accessed the info page.";
        CROW_LOG_INFO<<"Serving the information.";
        std::string res = "Info:\n";
        res+= "Method: " + method_string(req.method) + "\n";
        res+= "URL: " + req.url + "\n";
        return res;
    });

//RETURN IP CASE
    CROW_ROUTE(app,"/getip")([](const crow::request& req){
        return "Your ip: "+ req.remote_ip_address;
    });

//Echo Case
    CROW_ROUTE(app, "/echo").methods(crow::HTTPMethod::POST)([](const crow::request& req){
        auto data = crow::json::load(req.body);

        if(!data) return crow::response(400, "Invalid JSON.");

        crow::json::wvalue respo;
        respo["received"] = data;
        respo["message"] = "Here is your data.";

        crow::response res;
        res.set_header("Content-Type", "application/json");
        res.code = 200;
        res.body = respo.dump();
        return res;
    });

//404 Case
    CROW_CATCHALL_ROUTE(app)([](const crow::request& req){
        CROW_LOG_WARNING<<"Someone accessed a page that does not exist.";
        return crow::response(404, "The page at " + req.url + ", unfortunately for you, not found.\n");
    });
    
//Running the Program
    CROW_LOG_INFO<<"Starting the Server.";
    // app.port(18080).ssl_file("cert.pem","key.pem");
    app.port(18080).multithreaded().run();

    return 0;
}
