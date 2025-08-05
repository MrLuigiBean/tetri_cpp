#include "IO.h"

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

IO::IO()
{
}

void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, color pC)
{
    static_cast<void>(pX1);
    static_cast<void>(pY1);
    static_cast<void>(pX2);
    static_cast<void>(pY2);
    static_cast<void>(pC);
}

void IO::ClearScreen()
{
}

int IO::GetScreenHeight()
{
    return 0;
}

int IO::InitGraph()
{
    return 0;
}

int IO::Pollkey()
{
    return 0;
}

int IO::Getkey()
{
    return 0;
}

int IO::IsKeyDown(int pKey)
{
    static_cast<void>(pKey);
    return 0;
}

void IO::UpdateScreen()
{
}
