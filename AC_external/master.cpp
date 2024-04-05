#include "master.h"
#include <iostream>
#include "offsets.h"


master::master(const processUtils& pUtils) : pUtils(pUtils) {
}

// Function definition
const DWORD master::getLocalPLayer()
{
    return 1;
}
