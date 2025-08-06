#include "IO.h"

/// @brief A copy of the address of the AppState pointer passed to SDL's `appstate`.
/// Used to handle rendering.
AppState* IO::appState = nullptr;

namespace IO
{
    /// @brief Represents a color with red, green blue and alpha transparency.
    ///        Values range from 0 to 255.
    struct Color
    {
        Uint8
            /// @brief Value of red channel, ranging from 0 to 255.
            r,
            /// @brief Value of green channel, ranging from 0 to 255.
            g,
            /// @brief Value of blue channel, ranging from 0 to 255.
            b,
            /// @brief Value of the alpha transparency channel, ranging from 0 to 255.
            a;
    };

    /// @brief Helper for saving the currently set color before modifications and
    ///        applying it when modifications are complete.
    ///        Kept inside namespace IO to retain appState information.
    struct SaveAndLoadDrawColor
    {
        /// @brief This variable holds the SDL draw color before modification.
        Color col;

        /// @brief Saves the current draw color to be loaded later.
        SaveAndLoadDrawColor()
        {
            SDL_GetRenderDrawColor(appState->renderer, &col.r, &col.g, &col.b, &col.a);
        }

        /// @brief Loads the saved draw color to SDL.
        ~SaveAndLoadDrawColor()
        {
            SDL_SetRenderDrawColor(appState->renderer, col.r, col.g, col.b, col.a);
        }

        /// @brief Deleted. Only a single instance is required in a function body.
        SaveAndLoadDrawColor(const SaveAndLoadDrawColor&) = delete;

        /// @brief Deleted. Only a single instance is required in a function body.
        SaveAndLoadDrawColor(SaveAndLoadDrawColor&&) = delete;

        /// @brief Deleted. There are no other instances being assigned in a function body.
        SaveAndLoadDrawColor& operator=(const SaveAndLoadDrawColor&) = delete;

        /// @brief Deleted. There are no other instances being assigned in a function body.
        SaveAndLoadDrawColor& operator=(SaveAndLoadDrawColor&&) = delete;
    };

    /// @brief Represents whether a given key is pressed this frame.
    bool keyStates[numInputs] = { false };
}

/// @brief Returns a IO::Color with values from 0 to 255.
/// @param label A ::ColorLabel representing a color.
/// @return A IO::Color corresponding to the given color label.
static IO::Color GetColorFromLabel(ColorLabel label)
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

/// @brief Casts the given value to an `int`.
/// @param input The IO::Inputs enumeration value to cast.
/// @return The integer value of the given enumeration.
inline static int Cast(IO::Inputs input)
{
    return static_cast<int>(input);
}

/// @brief Draws a filled-in rectangle with the given coordinates and color.
/// @param posX1 The x-coordinate of the upper-left corner of the rectangle.
/// @param posY1 The y-coordinate of the upper-left corner of the rectangle.
/// @param posX2 The x-coordinate of the lower-right corner of the rectangle.
/// @param posY2 The y-coordinate of the lower-right corner of the rectangle.
/// @param colorLabel The color to fill in the rectangle with.
void IO::DrawRectangle(int posX1, int posY1, int posX2, int posY2, ColorLabel colorLabel)
{
    SaveAndLoadDrawColor _;

    SDL_Rect rect
    {
        .x = posX1 < posX2 ? posX1 : posX2,
        .y = posY1 < posY2 ? posY1 : posY2,
        .w = abs(posX1 - posX2),
        .h = abs(posY1 - posY2),
    };
    SDL_FRect frect{};
    SDL_RectToFRect(&rect, &frect);

    Color col = GetColorFromLabel(colorLabel);
    SDL_SetRenderDrawColor(appState->renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(appState->renderer, &frect);
}

/// @brief Clears the screen to black.
void IO::ClearScreen()
{
    SaveAndLoadDrawColor _;

    SDL_SetRenderDrawColor(appState->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(appState->renderer);
}

/// @brief Draws all visuals to be rendered to the screen.
void IO::UpdateScreen()
{
    SDL_RenderPresent(appState->renderer);
}

/// @brief Stores the state of all IO::Inputs that are used by the application.
/// @param keyEvent An event from SDL that has information on the key pressed.
void IO::PollKey(SDL_KeyboardEvent keyEvent)
{
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

/// @brief Returns whether the button for the given action was pressed.
/// @param action The action from IO::Inputs to query.
/// @return Returns true if the button was pressed this frame, false otherwise.
bool IO::IsKeyDown(Inputs action)
{
    return keyStates[Cast(action)];
}

/// @brief Reset all key state information in preparation for next frame.
void IO::ClearKeyStates()
{
    for (int i = 0; i < numInputs; ++i)
        keyStates[i] = false;
}
