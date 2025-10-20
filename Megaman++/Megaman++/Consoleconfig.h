#pragma once
#include <windows.h>

inline void posicionarConsole(int x, int y)
{
    HWND console = GetConsoleWindow();
    if (!console) return;

    RECT rect;
    GetWindowRect(console, &rect);

    int largura = rect.right - rect.left;
    int altura = rect.bottom - rect.top;

    MoveWindow(console, x, y, largura, altura, TRUE);
}