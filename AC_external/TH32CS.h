#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

/// <summary>
/// This class is responsible for getting the first vital information of the game
/// </summary>

class processUtils
{
private:
	HANDLE gameHandle;
	const DWORD getProcessId(const char* sProcName);
public:
	DWORD procID;

	//functions
	const HANDLE getHandle() { return this->gameHandle; }
	const bool getProcessHandle(const char* sProcName);
	static const uintptr_t GetModuleBaseAddress(const DWORD procID, const wchar_t* moduleName);
};
