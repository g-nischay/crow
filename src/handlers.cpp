#include "handlers.h"
#include "crowTools.h"
#include "globals.h"
#include <crow.h>
#include <random>

crow::response homeHandle(std::mt19937_64& mt){
        CROW_LOG_DEBUG<<"Someone is accessing the homepage";
        CROW_LOG_INFO<<"Serving the homepage to a certain someone.";

        auto page = crow::mustache::load("home_page.html");
        crow::mustache::context ctx;
        ctx["color"] = random_color(mt);
        ctx["content_time"] = std::to_string(G_HOMEPAGE_REFRESH_TIME_PERIOD);
        ctx["name_url"] = "https://localhost:18080/hello/";
        ctx["calc_url"] = "https://localhost:18080/calc/";
        return page.render(ctx);
    };

crow::response operationHandle(int a, int b){
        CROW_LOG_DEBUG<<"Someone is using the calculator.";
        CROW_LOG_INFO<<"Presenting the output for calculator.";
        std::string res;
        res += std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(a+b) + '\n';
        res += std::to_string(a) + " - " + std::to_string(b) + " = " + std::to_string(a-b) + '\n';
        res += std::to_string(a) + " * " + std::to_string(b) + " = " + std::to_string(a*b) + '\n';
        if(b) res += std::to_string(a) + " / " + std::to_string(b) + " = " + std::to_string(static_cast<float>(a)/b) + '\n';
        else res += "can't divide " + std::to_string(a) + " by 0.\n";
        return res;
    }

crow::response uploadHandle(const crow::request& req){
        crow::multipart::message multipart_message(req);

        auto desc_part = multipart_message.get_part_by_name("description");
        auto desc_file = multipart_message.get_part_by_name("file");

        std::string desc_text = desc_part.body.empty()? "(none)":desc_part.body;

        std::string file_name;
        int file_size{0};

        if(desc_file.body.empty()) file_name = "(no name)";
        else{file_name = desc_file.get_header_object("Content-Disposition").params.find("filename")->second;
            file_size = desc_file.body.size();
        }
        std::string res{};
        res+="Description: "+ desc_text +"\n";
        res+="File Name: "+ file_name +"\n";
        if(file_size) res+="File Size: " + std::to_string(file_size) +" Bytes\n";

        return res;
    }

crow::response searchHandle(const crow::request& req){
    auto name = req.url_params.get("name");
    auto age = req.url_params.get("age");
    std::string res{};
    res+= "Name: " + static_cast<std::string>(name? name:"(no name)") + "\n";
    res+= "Age: " + static_cast<std::string>(age?age:"(no age)") + "\n";
    return res;
}
