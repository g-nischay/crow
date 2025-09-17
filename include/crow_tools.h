#ifndef CROWTOOLS_H
#define CROWTOOLS_H

#include "crow.h"
#include <string>
#include <random>
#include <cstdint>

std::string random_color(std::mt19937_64& mt);

std::string intToHex(std::uint16_t n);

std::string method_string(crow::HTTPMethod method);
#endif
