#pragma once

#include <SDL3/SDL.h>

class Game; // full definition in Game.h

/// @brief This represents the overall state of the SDL application.
struct AppState
{
    /// @brief The pointer to the window created by SDL.
    SDL_Window* window = nullptr;
    
    /// @brief The pointer to the renderer created by SDL.
    SDL_Renderer* renderer = nullptr;

    /// @brief The pointer to the created game information.
    Game* game = nullptr;
};
