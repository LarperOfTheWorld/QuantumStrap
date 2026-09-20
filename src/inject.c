#include <windows.h>
#include "fastflags.h"
#include "blacklist.h"

// Inject this DLL into the Target Process
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            // Prevents thread from being detached before we finish
            DisableThreadLibraryCalls(hModule);
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_ATTACH:
            // Check Blacklist first
            char targetName[256];
            GetModuleFileNameA(GetModuleHandleA(NULL), targetName, sizeof(targetName));

            for(int i=0; i < 256; i++){
                if(strstr(targetName, blacklist[i])) continue; // Skip
            }

            // Init Memory
            InitFastFlags(); 
            
            // Create the Cheat Thread
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RenderCheatLoop, hModule, 0, NULL);
            break;
    }
    return TRUE;
}

void RenderCheatLoop(HMODULE mod) {
    while(1) {
        // Logic to keep cheats active
        Sleep(10);
    }
}
