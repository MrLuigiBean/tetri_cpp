#pragma once
#ifndef IO_H
#define IO_H

#include "AppState.h"

// -- Enums --

enum ColorLabel { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE };

namespace IO
{
    extern AppState* appState;

    void DrawRectangle(int pX1, int pY1, int pX2, int pY2, ColorLabel colorLabel);
    void ClearScreen();
    void UpdateScreen();

    enum class Inputs { RIGHT, LEFT, UP, DOWN, ROTATE, TOTAL };
    constexpr int numInputs = static_cast<int>(IO::Inputs::TOTAL);

    void PollKey(SDL_KeyboardEvent keyEvent);
    int IsKeyDown(Inputs action);
    void ClearKeyStates();
};

#endif // IO_H
