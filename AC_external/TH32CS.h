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
	DWORD procID = 0;
	HANDLE gameHandle;
	const bool getProcessId(const char* sProcName);
public:
	 const HANDLE getProcessHandle(const char* sProcName);
	const uintptr_t GetModuleBaseAddress(const wchar_t* moduleName);
};
