#pragma once

#include <SDL3/SDL.h>

struct AppState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
