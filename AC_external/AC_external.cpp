#include <iostream>
#include "TH32CS.h"
#include "master.h"
int main() {
    try {
        std::unique_ptr<master> gameMaster = std::make_unique<master>("ac_client.exe");
    }   
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    return 0;
}
