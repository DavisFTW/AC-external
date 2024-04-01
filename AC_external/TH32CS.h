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
public:
	static const DWORD getProcessId(const char* sProcName);
	static const DWORD getModuleId(const DWORD procID, const char* moduleName);														 

};
