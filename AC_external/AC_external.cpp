#include <iostream>
#include "TH32CS.h"
#include "master.h"
int main() {
    try {
        const auto handle = processUtils::getProcessHandle("ac_client.exe");

        std::unique_ptr<master> m = std::make_unique<master>(handle);
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    return 0;
}
