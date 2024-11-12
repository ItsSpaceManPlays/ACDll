#include <iostream>
#include <Windows.h>
#include <thread>
#include "constants.h"
#include "genCode.h"
#include "offsets.h"

bool running = true;
bool infHealth = false;
bool infAmmo = false;

void hook() {
	while (running)
	{
		if (infHealth) {
			localPlayerPtr->health = 1337;
		}
		if (infAmmo) {
			weapon* currWeapon = localPlayerPtr->currweapon;
			currWeapon->ammoptr->ammo = 21;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	FreeLibraryAndExitThread(hModule, 0);
}

void console(HMODULE hModule) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONIN$", "r", stdin);
	std::cout << "Dll injection successfull" << std::endl;
	std::cout << "Offsets        :: Addresses" << std::endl;
	std::cout << "ac_client.exe  :: 0x" << exeBaseAddress << std::endl;
	std::cout << "EntityListPtr  :: 0x" << entityListPtr << std::endl;
	std::cout << "localPlayerPtr :: 0x" << localPlayerPtr << std::endl;
	std::cout << "   + health    :: 0x" << Offsets::healthOffset << std::endl;

	std::cout << std::endl;
	while (true) {
		std::string input;
		std::cout << "> ";
		std::cin >> input;
		if (input == "exit") {
			std::cout << "Dll uninjected, you may close the console" << std::endl;
			break;
		}
		if (input == "help") {
			std::cout << "up:   move the player upwards 5 meters\n";
		}
		if (input == "up") {
			localPlayerPtr->position.y += 5;
			continue;
		}
		if (input == "getptr") {
			std::cout << "Local Player Ptr: 0x" << localPlayerPtr << " ModuleBase: 0x" << exeBaseAddress << std::endl;
			continue;
		}
		if (input == "sethp") {
			int hpvalue;
			printf("Enter HP> ");
			if (scanf_s("%d", &hpvalue) != 1) {
				std::cout << "Please enter a valid integer" << std::endl;
				continue;
			}
			localPlayerPtr->health = hpvalue;
			std::cout << "Player health set to: " << hpvalue << std::endl;
			continue;
		}
		if (input == "infhp") {
			infHealth = !infHealth;
			if (infHealth) {
				printf("Inf health: enabled\n");
			}
			else {
				printf("Inf health: disabled\n");
			}
			continue;
		}
		if (input == "infammo") {
			infAmmo = !infAmmo;
			if (infAmmo) {
				printf("Inf ammo: enabled\n");
			}
			else {
				printf("Inf ammo: disabled\n");
			}
			continue;
		}
		if (input == "entlist") {
			if (*entityListSizePtr == 0 || entityListPtr == nullptr) {
				std::cout << "There are no other players, entity list ptr: 0x" << entityListPtr << std::endl;
				continue;
			}
			std::cout << "There are " << *entityListSizePtr << " players" << std::endl;
			for (int i = 0; i < *entityListSizePtr; i++) {
				Player* currentPlayer = entityListPtr->players[i];

				if (currentPlayer == nullptr) {
					std::cout << "No player found at 0x" << entityListPtr << " -> 0x" << &currentPlayer << std::endl;
					break;
				}

				std::cout << "Entity 0x" << currentPlayer << " " << i << " health: " << currentPlayer->health << std::endl;
			}
			continue;
		}
		printf("Invalid command!\n");
	}
	FreeConsole();
	running = false;
	ExitThread(0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, hModule, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}