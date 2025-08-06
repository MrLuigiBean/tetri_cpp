#pragma once
#ifndef IO_H
#define IO_H

#include "AppState.h"

/// @brief Provides quick acces to simple colors.
enum ColorLabel
{
    /// ( 0, 0, 0, 255 )
    BLACK,

    /// ( 255, 0, 0, 255 )
    RED,

    /// ( 0, 255, 0, 255 )
    GREEN,

    /// ( 0, 0, 255, 255 )
    BLUE,

    /// ( 0, 255, 255, 255 )
    CYAN,

    /// ( 255, 0, 255, 255 )
    MAGENTA,

    /// ( 255, 255, 0, 255 )
    YELLOW,

    /// ( 255, 255, 255, 255 )
    WHITE,
};

namespace IO
{
    /// @brief A copy of the address of the AppState pointer passed to SDL's `appstate`.
    /// Used to handle rendering.
    extern AppState* appState;

    /// @brief Draws a filled-in rectangle with the given coordinates and color.
    /// @param posX1 The x-coordinate of the upper-left corner of the rectangle.
    /// @param posY1 The y-coordinate of the upper-left corner of the rectangle.
    /// @param posX2 The x-coordinate of the lower-right corner of the rectangle.
    /// @param posY2 The y-coordinate of the lower-right corner of the rectangle.
    /// @param colorLabel The color to fill in the rectangle with.
    void DrawRectangle(int posX1, int posY1, int posX2, int posY2, ColorLabel colorLabel);

    /// @brief Clears the screen to black.
    void ClearScreen();

    /// @brief Draws all visuals to be rendered to the screen.
    void UpdateScreen();

    /// @brief This class represents what possible inputs are present for this application.
    enum class Inputs { RIGHT, LEFT, UP, DOWN, ROTATE, TOTAL };

    /// @brief The total number of inputs possible, as described in IO::Inputs.
    constexpr int numInputs = static_cast<int>(IO::Inputs::TOTAL);

    /// @brief Stores the state of all IO::Inputs that are used by the application.
    /// @param keyEvent An event from SDL that has information on the key pressed.
    void PollKey(SDL_KeyboardEvent keyEvent);

    /// @brief Returns whether the button for the given action was pressed.
    /// @param action The action from IO::Inputs to query.
    /// @return Returns true if the button was pressed this frame, false otherwise.
    bool IsKeyDown(Inputs action);

    /// @brief Reset all key state information in preparation for next frame.
    void ClearKeyStates();
};

#endif // IO_H
