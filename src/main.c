#include <windows.h>
#include <stdio.h>
#include "launcher.h"

// UI Implementation (Dear ImGui wrapper)
// For the full UI visual to work, this needs the ImGui .lib/.h files linked.
// This is the skeleton logic.

int WINAPI WinMain(HINSTANCE h, HINSTANCE prev, LPSTR cmd, int nCmdShow) {
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)(DWORD)&WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = h;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "QuantumStrap";
    wc.hIconSm = wc.hIcon;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Failed to Register Window!", "Error", MB_ICONHAND);
        return 0;
    }

    g_hWnd = CreateWindowEx(WS_EX_APPWINDOW, "QuantumStrap", "Foxname - Universal Framework", 
                            WS_OVERLAPPEDWINDOW, 0, 0, 500, 400, NULL, NULL, h, NULL);

    ShowWindow(g_hWnd, nCmdShow);

    // Start Render Loop
    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        RenderUI(); // Draw the screen (ImGui)
    }
    return msg.wParam;
}

// Placeholder for the WndProc
int WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
