#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"

/// @brief Width of each of the two lines that delimit the board
constexpr int BOARD_LINE_WIDTH = 8;

/// @brief Width and Height of each block of a piece
constexpr int BLOCK_SIZE = 32;

/// @brief Center position of the board from the left of the screen
constexpr int BOARD_POSITION = 1920 / 2;

/// @brief Board width in blocks
constexpr int BOARD_WIDTH = 10;

/// @brief Board height in blocks
constexpr int BOARD_HEIGHT = 20;

/// @brief Minimum vertical margin for the board limit
constexpr int MIN_VERTICAL_MARGIN = 20;

/// @brief Minimum horizontal margin for the board limit
constexpr int MIN_HORIZONTAL_MARGIN = 20;

/// @brief Number of horizontal and vertical blocks of a matrix piece
constexpr int PIECE_BLOCKS = 5;

/// @brief This class manages the placement of pieces in the game board.
class Board
{
public:

    /// @brief Initialises the board with a given height.
    /// @param height The height of the board in pixels.
    Board(int height);

    /// @brief Returns the given horizontal coordinate in pixels.
    /// @param posX The x-coordinate of the block.
    /// @return Returns the horizontal position in pixels.
    int GetXPosInPixels(int posX) const;

    /// @brief Returns the given vertical coordinate in pixels.
    /// @param posY The y-coordinate of the block.
    /// @return Returns the vertical position in pixels.
    int GetYPosInPixels(int posY) const;

    /// @brief Checks if the given board position is occupied.
    /// @param posX The x-coordinate to check.
    /// @param posY The y-coordinate to check.
    /// @return `true` if the block's position is occupied, `false` otherwise.
    bool IsFreeBlock(int posX, int posY) const;

    /// @brief Check if a given piece can be stored at this position on the board.
    /// @param posX The x-coordinate of the position to check.
    /// @param posY The y-coordinate of the position to check.
    /// @param piece The kind of piece.
    /// @param rotation The rotation of the piece.
    /// @return `true` if the movement is allowed, `false` otherwise.
    bool IsPossibleMovement(int posX, int posY, int piece, int rotation) const;

    /// @brief Store a piece in the board by filling in its blocks.
    /// @param pieceState The state of a piece.
    void StorePiece(const PieceState& pieceState);

    /// @brief Determines which lines to clear and removes them from the board.
    void DeletePossibleLines();

    /// @brief Determines if blocks have reached the top of the screen.
    /// @return Returns `true` is there a blocks at the top, `false` otherwise.
    bool IsGameOver() const;

private:

    enum
    {
        /// Represents a free position on the board.
        POS_FREE,

        /// Represents a filled position on the board.
        POS_FILLED
    };

    /// @brief Represents the board containing the blocks from fallen pieces.
    char board[BOARD_WIDTH][BOARD_HEIGHT] = { POS_FREE };

    /// @brief The height of the board in pixels.
    int boardHeight = 0;

    /// @brief Initializes all board blocks to Board::POS_FREE.
    void InitBoard();

    /// @brief Deletes a line of the board by moving all lines above down.
    /// @param posY Vertical position of blocks in the line to delete.
    void DeleteLine(int posY);
};

#endif // BOARD_H
