#include <iostream>
#include "TH32CS.h"
int main() {
	DWORD pid = 0;
	pid = TH32CS::getProcessId("ac_client.exe");
	const auto modulebaseAddr = TH32CS::getModuleId(pid, "")
	return 0;
}
