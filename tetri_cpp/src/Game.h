#pragma once
#ifndef GAME_H
#define GAME_H

#include "Board.h"

/// @brief Number of milliseconds that the piece remains before going 1 block down
constexpr int PIECE_MOVEMENT_TIME_INTERVAL = 700;

/// @brief This represents the game and its necessary operations.
class Game
{
public:

    /// @brief Constructs the board of the game using a given size.
    /// @param height The height of the screen in pixels.
    Game(int height);

    /// @brief Draws the board, the current piece and the next piece.
    void DrawScene();

    /// @brief Sets the next piece as the current one and resets its position,
    /// after which a new "next piece" is selected.
    void CreateNewPiece();

    /// @brief The board that holds fallen blocks.
    Board board;

    /// @brief Contains information of the piece currently falling.
    PieceState fallingPiece;

private:

    /// @brief The screen height in pixels.
    int screenHeight = 0;

    /// @brief x-position of the next piece
    int nextPosX = 0;
    /// @brief y-position of the next piece
    int nextPosY = 0;
    /// @brief Kind of the next piece
    int nextPiece = 0;
    /// @brief Rotation of the next piece
    int nextRotation = 0;

    /// @brief Returns a random number between two integers.
    /// @param a The lower end of the range.
    /// @param b The upper end of the range.
    /// @return A random number in the range [a, b]
    int GetRand(int pA, int pB);

    /// @brief Selects the first and next piece randomly.
    void InitGame();

    /// @brief Draws a given piece.
    /// @param posX The x-coordinate of the piece.
    /// @param posY The y-coordinate of the piece.
    /// @param piece The kind of the piece.
    /// @param rotation The rotation of the piece.
    void DrawPiece(int posX, int posY, int piece, int rotation) const;

    /// @brief Draws the board's delimiters and existing board blocks.
    void DrawBoard() const;
};

#endif // GAME_H
