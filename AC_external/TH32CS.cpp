#include "TH32CS.h"
#include <string_view>
#include <memory>
#include <windows.h>
#include <TlHelp32.h>
#include <stdexcept>

const bool processUtils::getProcessHandle(const char* sProcName)
{
	this->procID = processUtils::getProcessId(sProcName);

	//std::cout << this->procID;

	const auto handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	
	if(handle == nullptr)
	{
		throw std::runtime_error("Error occurred while opening the process handle!");
	}

	this->gameHandle = handle;
	return true;
}

const DWORD processUtils::getProcessId(const char* sProcName) {

	std::unique_ptr<void, decltype(&CloseHandle)>
		hProcessSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0),
			&CloseHandle);

	if (hProcessSnap.get() == nullptr) {
		throw std::runtime_error("hProcessSnap contains invalid handle value !");
	}

	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap.get(), &pEntry)) {
		throw std::runtime_error("Error getting the first process");
	}

	do {
		char szExeFile[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, pEntry.szExeFile, -1, szExeFile, MAX_PATH, NULL, NULL);

		if (strcmp(sProcName, szExeFile) == 0) {
			return pEntry.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap.get(), &pEntry));

	const DWORD lastError = GetLastError();
	SetLastError(ERROR_SUCCESS);
	if (lastError != ERROR_NO_MORE_FILES) {
		throw std::runtime_error("Error occurred while enumerating processes!" + std::to_string(lastError));
	}
	throw std::runtime_error("No Process was found with the given name!");
}

const uintptr_t processUtils::GetModuleBaseAddress(const DWORD procID, const wchar_t* moduleName){

	std::unique_ptr<void, decltype(&CloseHandle)>
		hProcessSnap(CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID),
																					&CloseHandle);

	if (hProcessSnap.get() == nullptr) {
		throw std::runtime_error("hProcessSnap contains invalid handle value !");
		}

		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (!Module32First(hProcessSnap.get(), &modEntry))
		{
			throw std::runtime_error("Error getting the first module");
		}
		
		do
		{
			if (!_wcsicmp(modEntry.szModule, moduleName))
			{
				const auto modBaseAddr = reinterpret_cast<uintptr_t>(modEntry.modBaseAddr);
				//std::cout << "modBaseAddr" << std::hex << modBaseAddr << std::endl;
				return modBaseAddr;
			}
		} while (Module32Next(hProcessSnap.get(), &modEntry));

		const DWORD lastError = GetLastError();
		SetLastError(ERROR_SUCCESS);

		if (lastError != ERROR_NO_MORE_FILES) {
			throw std::runtime_error("Error occurred while enumerating modules!" + std::to_string(lastError));
		}

		throw std::runtime_error("No module was found with the given name!");
}

