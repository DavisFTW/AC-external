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
	static const DWORD getProcessId(const char* sProcName);
	static const uintptr_t GetModuleBaseAddress(const DWORD procID, const wchar_t* moduleName);
public:
	static const HANDLE getProcessHandle(const char* sProcName);
};
