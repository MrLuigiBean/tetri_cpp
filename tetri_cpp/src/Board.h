#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"

/// @brief Width of each of the two lines that delimit the board
constexpr int BOARD_LINE_WIDTH = 8;

/// @brief Width and Height of each block of a piece
constexpr int BLOCK_SIZE = 32;

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

    /// @brief Initializes the board.
    Board();

    /// @brief Checks if the given board position is occupied.
    /// @param posX The x-coordinate to check.
    /// @param posY The y-coordinate to check.
    /// @return `true` if the block's position is occupied, `false` otherwise.
    bool IsFreeBlock(int posX, int posY) const;

    /// @brief Check if a given piece can be stored at this position on the board.
    /// @param pieceState The state of a piece.
    /// @return `true` if the movement is allowed, `false` otherwise.
    bool IsPossibleMovement(const PieceState& pieceState) const;

    /// @brief Store a piece in the board by filling in its blocks.
    /// @param pieceState The state of a piece.
    void StorePiece(const PieceState& pieceState);

    /// @brief Determines which lines to clear and removes them from the board.
    void DeletePossibleLines();

    /// @brief Determines if blocks have reached the top of the screen.
    /// @return Returns `true` is there a blocks at the top, `false` otherwise.
    bool IsGameOver() const;

    /// @brief Moves a piece to its bottom-most valid position.
    /// @param pieceState The piece to drop.
    void DropPiece(PieceState& pieceState) const;

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

    /// @brief Initializes all board blocks to Board::POS_FREE.
    void InitBoard();

    /// @brief Deletes a line of the board by moving all lines above down.
    /// @param posY Vertical position of blocks in the line to delete.
    void DeleteLine(int posY);
};

#endif // BOARD_H
