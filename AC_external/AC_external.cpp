#include <iostream>
#include "TH32CS.h"

int main() {
    try {
        const auto pid = processUtils::getProcessId("ac_client.exe");
        std::cout << pid << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    return 0;
}
