#include "secret.h"
#include "middleware.h"
#include <crow.h>
#include <iostream>
void AdminGuard::before_handle(crow::request& req, crow::response& res, context& ctx){
    // std::cout<<"[DEBUG] Admin IP: "<<ADMIN_IP<<'\n';
    // std::cout<<"[DEBUG] Request IP: "<<req.remote_ip_address<<'\n';
    if(req.remote_ip_address != ADMIN_IP){
        // std::cout<<"[DEBUG] Access Denied: Unauthorized ID detected.\n";
        res.code = 403;
        res.end();
        return;
    }
    // else std::cout<<"[DEBUG] Access Granted: Valid ID.\n";
}
void AdminGuard::after_handle(crow::request& req, crow::response& res, context& ctx){}
