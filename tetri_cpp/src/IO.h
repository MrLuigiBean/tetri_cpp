#pragma once
#ifndef IO_H
#define IO_H

// -- Includes --

#ifndef LINUX
#include "SDL3/SDL.h"
// #include "SDL3/SDL_GfxPrimitives/SDL_gfxPrimitives.h"
#else
#include <SDL/SDL.h>
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"
#endif
// #pragma comment (lib, "SDL3/lib/SDL.lib")
// #pragma comment (lib, "SDL3/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

// -- Enums --

enum color { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX }; // Colors

// ---------------------------
// IO
// ---------------------------

class IO
{
public:

    IO();

    void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
    void ClearScreen();
    int GetScreenHeight();
    int InitGraph();
    int Pollkey();
    int Getkey();
    int IsKeyDown(int pKey);
    void UpdateScreen();

};

#endif // IO_H
