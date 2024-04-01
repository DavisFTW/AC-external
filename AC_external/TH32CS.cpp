#include "TH32CS.h"
#include <string_view>
#include <memory>
const DWORD TH32CS::getProcessId(const char* sProcName) {

	// a lot better then using handle as we dont have to worry abt leaking handles E.G exceptions and non existing closeHandle function calls
	std::unique_ptr<void, decltype(&CloseHandle)> 
					hProcessSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0), 
					&CloseHandle);

	if (hProcessSnap.get() == nullptr) {
		throw std::runtime_error("hProcessSnap contains invalid handle value !");
	}

	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	do {
		if (std::string_view(sProcName) == pEntry.szExeFile) {
			return pEntry.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap.get(), &pEntry));
	
	// ERROR ERROR ERROR
	const DWORD lastError = GetLastError();
	SetLastError(ERROR_SUCCESS);
	if (lastError != ERROR_NO_MORE_FILES) {
		throw std::runtime_error("Error occurred while enumerating processes!" + std::to_string(lastError));
	}
	throw std::runtime_error("No Process was found with the given name!");
}

const DWORD TH32CS::getModuleId(const DWORD procID, const char* moduleName){
	std::unique_ptr<void, decltype(&CloseHandle)>
		moduleSnap(CreateToolhelp32Snapshot(TH32CS_SNAPMODULE || TH32CS_SNAPMODULE32, 0),
			&CloseHandle);

	if (moduleSnap.get() == nullptr) {
		throw std::runtime_error("module snapshot contains invalid handle value");
	}

	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(MODULEENTRY32);

	do{
		if (std::string_view(moduleName) == mEntry.szModule) {
			return reinterpret_cast<DWORD>(mEntry.modBaseAddr);
		}
	} while(Module32Next(moduleSnap.get(), &mEntry));

	const DWORD lastError = GetLastError();
	SetLastError(ERROR_SUCCESS);

	if (lastError != ERROR_NO_MORE_FILES) {
		throw std::runtime_error("Error occurred while enumerating modules!" + std::to_string(lastError));
	}

	throw std::runtime_error("No module was found with the given name!");
}

