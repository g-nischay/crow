#include "secret.h"
#include "middleware.h"
#include <crow.h>

void AdminGuard::after_handle(crow::request& req, crow::response& res, context& ctx){
    if(req.remote_ip_address != ADMIN_IP){
        res.code = 403;
        res.end();
    }
}
void AdminGuard::before_handle(crow::request& req, crow::response& res, context& ctx){}
