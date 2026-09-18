#include <stdio.h>
#include <windows.h>
#include "inject.h"

// Quantum Inject hotkey listener. The attach + execution engine lives in
// the distributed release binary; the open-source build exposes the same
// hotkey surface so behavior can be reviewed.

static int g_listenerRunning = 0;

static DWORD WINAPI hotkeyThread(LPVOID param) {
    (void)param;
    while (g_listenerRunning) {
        if (GetAsyncKeyState(VK_F6) & 1)
            printf("[Inject] F6 pressed — attach point reached\n");
        Sleep(50);
    }
    return 0;
}

void inject_start_listener(void) {
    g_listenerRunning = 1;
    CreateThread(NULL, 0, hotkeyThread, NULL, 0, NULL);
}
