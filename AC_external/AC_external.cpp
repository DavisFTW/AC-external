#include <iostream>
#include "TH32CS.h"
#include "master.h"

namespace ctx {
    processUtils pUtils;
    master* mast = nullptr;
}

int main() {
    try {
        const auto procID = ctx::pUtils.getProcessHandle("ac_client.exe");
        ctx::mast = new master(ctx::pUtils); // Passing ProcessUtils instance to Master
        const auto x = ctx::mast->getLocalPLayer();
        delete ctx::mast;
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    return 0;
}
