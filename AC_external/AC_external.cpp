#include <iostream>
#include "TH32CS.h"

int main() {
    try {
        const auto pid = processUtils::getProcessHandle("ac_client.exe");


    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    return 0;
}
