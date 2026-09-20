#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <windows.h>

// The UI Loop Handle
extern HWND g_hWnd;
extern bool g_ShouldClose;
extern bool b_isInjecting;
extern bool b_isInjected;

// UI Callbacks
void RenderUI();
void LaunchThread(HMODULE mod, LPVOID param);

#endif
