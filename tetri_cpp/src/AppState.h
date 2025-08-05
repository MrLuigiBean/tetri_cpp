#pragma once

#include <SDL3/SDL.h>

class Game; // full definition in Game.h

struct AppState
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Game* game = nullptr;
};
