#pragma once
#ifndef IO_H
#define IO_H

#include "AppState.h"

// -- Enums --

enum ColorLabel { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE };

// ---------------------------
// IO
// ---------------------------

namespace IO
{
    extern AppState* appState;
    void DrawRectangle(int pX1, int pY1, int pX2, int pY2, ColorLabel pC);
    void ClearScreen();
    int Pollkey();
    int Getkey();
    int IsKeyDown(int pKey);
    void UpdateScreen();
};

#endif // IO_H
