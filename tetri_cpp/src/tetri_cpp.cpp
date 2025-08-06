/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "AppState.h"
#include "Game.h"
#include "IO.h"

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    static AppState state{};

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &state.window, &state.renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    int screenHeight;
    {
        int temp;
        SDL_GetRenderOutputSize(state.renderer, &temp, &screenHeight);
    }

    static Game game(screenHeight);
    state.game = &game;

    // store the window, renderer and game in appstate to be passed around in other SDL_App??? functions
    *appstate = &state;
    IO::appState = &state; // IO will need the references to the window and renderer

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    static_cast<void>(appstate);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE)
        return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP)
        IO::PollKey(event->key);

    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    AppState* state = static_cast<AppState*>(appstate);

    const char* message = "Hello World!";
    int w = 0, h = 0;

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(state->renderer, &w, &h);
    float x = (w - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2.0f;
    float y = (h - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2.0f;

    /* Draw the message */
    IO::ClearScreen();
    SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(state->renderer, x, y, message);
    state->game->DrawScene();
    IO::UpdateScreen();

    IO::ClearButtonDown();

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    static_cast<void>(appstate);
    static_cast<void>(result);
}
