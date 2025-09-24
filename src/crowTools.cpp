#include "crowTools.h"
#include <random>
#include <chrono>

std::string method_string(crow::HTTPMethod method){
    switch(method){
        case crow::HTTPMethod::GET: return "GET";
        case crow::HTTPMethod::POST: return "POST";
        case crow::HTTPMethod::PUT: return "PUT";
        case crow::HTTPMethod::DELETE: return "DELETE";
        case crow::HTTPMethod::HEAD: return "HEAD";
        case crow::HTTPMethod::OPTIONS: return "OPTIONS";
        case crow::HTTPMethod::PATCH: return "PATCH";
        default: return "UNKNOWN";
    }
}

char intHex(int n){
    if(n<=9) return '0'+n;
    return ('A'+n-10);
}

std::string intToHex(std::uint16_t n){
    if(n==0) return "000000";
    std::string str;
    while(n>0){
        str = intHex(n%16)+str;
        n/=16;
    }
    while(str.length()<6){
        str = '0' + str;
    }
    return str;
}

std::string random_color(std::mt19937_64& mt){
    static std::uniform_int_distribution<int> S_numb(1,16777216);
    int color = S_numb(mt);
    return intToHex(color);
}
