#pragma once
#include <Windows.h>
#include "TH32CS.h"
class master
{
private:
	const HANDLE gameHandle;
	const DWORD localPLayer = 0x018B0B8;  // have to add the base address of the game
public:
	bool getLocalPLayer();
};

