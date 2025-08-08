#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL_main.h>

#include "Game.h"
#include "IO.h"

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    static AppState state{};

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("tetri-cpp", 1920, 1080, SDL_WINDOW_RESIZABLE, &state.window, &state.renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_MaximizeWindow(state.window);

    int screenHeight;
    {
        int temp;
        SDL_GetRenderOutputSize(state.renderer, &temp, &screenHeight);
    }
    SDL_SetWindowMinimumSize(state.window, BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE);

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
    Game* game = static_cast<Game*>(state->game);
    static auto timeSinceLastMovement = SDL_GetTicks();

#pragma region Input

    if (IO::IsKeyDown(IO::Inputs::LEFT))
    {
        if (game->board.IsPossibleMovement(game->fallingPiece.If({ .modPosX = -1 })))
            game->fallingPiece.posX--;
    }

    if (IO::IsKeyDown(IO::Inputs::RIGHT))
    {
        if (game->board.IsPossibleMovement(game->fallingPiece.If({ .modPosX = +1 })))
            game->fallingPiece.posX++;
    }

    if (IO::IsKeyDown(IO::Inputs::DOWN))
    {
        if (game->board.IsPossibleMovement(game->fallingPiece.If({ .modPosY = +1 })))
            game->fallingPiece.posY++;
    }

    if (IO::IsKeyDown(IO::Inputs::ROTATE))
    {
        if (game->board.IsPossibleMovement(game->fallingPiece.If({ .modRotation = +1 })))
            game->fallingPiece.rotation = (game->fallingPiece.rotation + 1) % 4;
    }

    if (IO::IsKeyDown(IO::Inputs::DROP))
    {
        while (game->board.IsPossibleMovement(game->fallingPiece))
            game->fallingPiece.posY++;

        game->board.StorePiece(game->fallingPiece.If({ .modPosY = -1 }));

        game->board.DeletePossibleLines();

        if (game->board.IsGameOver())
        {
            return SDL_APP_SUCCESS;
        }

        game->CreateNewPiece();
    }

#pragma endregion

#pragma region Update

    auto currentTime = SDL_GetTicks();

    if ((currentTime - timeSinceLastMovement) > PIECE_MOVEMENT_TIME_INTERVAL)
    {
        if (game->board.IsPossibleMovement(game->fallingPiece.If({ .modPosY = +1 })))
        {
            game->fallingPiece.posY++;
        }
        else
        {
            game->board.StorePiece(game->fallingPiece);

            game->board.DeletePossibleLines();

            if (game->board.IsGameOver())
            {
                return SDL_APP_SUCCESS;
            }

            game->CreateNewPiece();
        }

        timeSinceLastMovement = SDL_GetTicks();
    }


#pragma endregion

#pragma region Render

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
    game->DrawScene();
    IO::UpdateScreen();

#pragma endregion

    IO::ClearKeyStates();

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    static_cast<void>(appstate);
    static_cast<void>(result);
}
