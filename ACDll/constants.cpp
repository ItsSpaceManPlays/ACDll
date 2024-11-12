#include "constants.h"
#include "offsets.h"

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = (uintptr_t)(hModule);

extern Player* localPlayerPtr = *(Player**)(exeBaseAddress + Offsets::localPlayer); // dereference pointer to player pointer

extern EntityList* entityListPtr = *(EntityList**)(exeBaseAddress + Offsets::entityTableOffset);
extern int* entityListSizePtr = (int*)(exeBaseAddress + Offsets::entityTableSizeOffset);