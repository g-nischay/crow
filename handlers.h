#ifndef HANDLERS_H
#define HANDLERS_H
#include <crow.h>
#include <random>

crow::response homeHandle(std::mt19937_64& mt);
crow::response uploadHandle(const crow::request& req);
crow::response searchHandle(const crow::request& req);
crow::response operationHandle(int a, int b);

#endif
