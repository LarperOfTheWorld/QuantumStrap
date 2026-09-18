#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "launcher.h"

// Locate the newest installed RobloxPlayerBeta.exe under
// %LOCALAPPDATA%\Roblox\Versions\<version>\ by comparing folder names
// (version folders sort chronologically).
static int findRobloxClient(char* outPath, size_t cap) {
    const char* local = getenv("LOCALAPPDATA");
    if (!local) return 1;

    char versionsDir[MAX_PATH];
    snprintf(versionsDir, sizeof versionsDir, "%s\\Roblox\\Versions", local);

    char pattern[MAX_PATH];
    snprintf(pattern, sizeof pattern, "%s\\*", versionsDir);

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) return 1;

    char best[MAX_PATH] = "";
    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) continue;
        if (fd.cFileName[0] == '.') continue;
        if (strcmp(fd.cFileName, best) > 0)
            strncpy(best, fd.cFileName, sizeof best - 1);
    } while (FindNextFileA(h, &fd));
    FindClose(h);

    if (!best[0]) return 1;

    snprintf(outPath, cap, "%s\\%s\\RobloxPlayerBeta.exe", versionsDir, best);
    if (GetFileAttributesA(outPath) == INVALID_FILE_ATTRIBUTES) return 1;
    return 0;
}

int launcher_start(void) {
    char exe[MAX_PATH];
    if (findRobloxClient(exe, sizeof exe) != 0) {
        printf("[Launcher] Roblox client not found\n");
        return 1;
    }

    STARTUPINFOA si = { 0 };
    si.cb = sizeof si;
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(exe, exe, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        return 1;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
