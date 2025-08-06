#include "IO.h"

// -- Includes --

#include "SDL3/SDL.h"

AppState* IO::appState = nullptr;

namespace IO
{
    /// @brief Helper for saving the currently set color before modifications and
    ///        applying it when modifications are complete.
    ///        Kept inside namespace IO to retain appState information.
    struct SaveAndLoadDrawColor
    {
        Uint8 r, g, b, a;

        SaveAndLoadDrawColor()
        {
            SDL_GetRenderDrawColor(appState->renderer, &r, &g, &b, &a);
        }

        ~SaveAndLoadDrawColor()
        {
            SDL_SetRenderDrawColor(appState->renderer, r, g, b, a);
        }

        SaveAndLoadDrawColor(const SaveAndLoadDrawColor&) = delete;
        SaveAndLoadDrawColor(SaveAndLoadDrawColor&&) = delete;

        SaveAndLoadDrawColor& operator=(const SaveAndLoadDrawColor&) = delete;
        SaveAndLoadDrawColor& operator=(SaveAndLoadDrawColor&&) = delete;
    };

    bool keyStates[numInputs] = { false };
}

struct Color { Uint8 r, g, b, a; };

static Color GetColorFromLabel(ColorLabel label)
{
    switch (label)
    {
    case BLACK:
        return { 0, 0, 0, 255 };
    case RED:
        return { 255, 0, 0, 255 };
    case GREEN:
        return { 0, 255, 0, 255 };
    case BLUE:
        return { 0, 0, 255, 255 };
    case CYAN:
        return { 0, 255, 255, 255 };
    case MAGENTA:
        return { 255, 0, 255, 255 };
    case YELLOW:
        return { 255, 255, 0, 255 };
    case WHITE:
        return { 255, 255, 255, 255 };
    default:
        return { 0, 0, 0, 0 };
    }
}

inline static int Cast(IO::Inputs input)
{
    return static_cast<int>(input);
}

void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, ColorLabel colorLabel)
{
    SaveAndLoadDrawColor _;

    SDL_Rect rect
    {
        .x = pX1 < pX2 ? pX1 : pX2,
        .y = pY1 < pY2 ? pY1 : pY2,
        .w = abs(pX1 - pX2),
        .h = abs(pY1 - pY2),
    };
    SDL_FRect frect{};
    SDL_RectToFRect(&rect, &frect);

    Color col = GetColorFromLabel(colorLabel);
    SDL_SetRenderDrawColor(appState->renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(appState->renderer, &frect);
}

void IO::ClearScreen()
{
    SaveAndLoadDrawColor _;

    SDL_SetRenderDrawColor(appState->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(appState->renderer);
}

void IO::UpdateScreen()
{
    SDL_RenderPresent(appState->renderer);
}

void IO::PollKey(SDL_KeyboardEvent keyEvent)
{
    // prevent repeat button presses - only one at a time!
    if (keyEvent.repeat)
        return;

    switch (keyEvent.key)
    {
    case SDLK_RIGHT:    IO::keyStates[Cast(Inputs::RIGHT)] = keyEvent.down; break;
    case SDLK_LEFT:     IO::keyStates[Cast(Inputs::LEFT)] = keyEvent.down; break;
    case SDLK_UP:       IO::keyStates[Cast(Inputs::UP)] = keyEvent.down; break;
    case SDLK_DOWN:     IO::keyStates[Cast(Inputs::DOWN)] = keyEvent.down; break;
    case SDLK_Z:        IO::keyStates[Cast(Inputs::ROTATE)] = keyEvent.down; break;
    default: break;
    }
}

int IO::IsKeyDown(Inputs action)
{
    return keyStates[Cast(action)];
}

void IO::ClearButtonDown()
{
    // Rotate is the only button that is not continous.
    // Up,down,left,right are all movements, they're allowed to be continous.
    keyStates[Cast(Inputs::ROTATE)] = false;
}
