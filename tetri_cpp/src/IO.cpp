#include "IO.h"

// -- Includes --

#include "SDL3/SDL.h"

AppState* IO::appState = nullptr;

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

//int IO::GetScreenHeight()
//{
//    int width, height;
//    SDL_GetRenderOutputSize(appState->renderer, &width, &height);
//    static_cast<void>(width); //unused
//    return height;
//}

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
