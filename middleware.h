#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <crow.h>

struct AdminGuard{
    struct context{};
    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};


#endif
