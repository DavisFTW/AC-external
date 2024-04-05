#include "TH32CS.h"

class master : public processUtils {
private:
    DWORD clientBaseAddr = 0;
    const DWORD localPLayer = 0x018B0B8;  // have to add the base address of the game
    const processUtils& pUtils; // Reference to ProcessUtils

public:
    master(const processUtils& pUtils);
    const DWORD getLocalPLayer();
};