#pragma once
#include <Windows.h>
#include "genCode.h"

extern HMODULE hModule;
extern uintptr_t exeBaseAddress;

extern Player* localPlayerPtr;
extern EntityList* entityListPtr;
extern int* entityListSizePtr;