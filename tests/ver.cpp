#include <crow.h>
#include <iostream>

int main() {
    std::cout << "Crow header found and compiled successfully!" << std::endl;
    
    // Try to create a simple app to test functionality
    crow::SimpleApp app;
    
    CROW_ROUTE(app, "/test")([]{
        return "Crow is working!";
    });
    
    std::cout << "Crow app created successfully - framework is functional" << std::endl;
    std::cout << "You can start the server by uncommenting the next line" << std::endl;
    // app.port(8080).run();  // Uncomment to actually start server
    
    return 0;
}
