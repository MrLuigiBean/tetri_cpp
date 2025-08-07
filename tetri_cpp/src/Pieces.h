#pragma once

#ifndef PIECES_H
#define PIECES_H

/// @brief Represents a state a piece can be in.
struct PieceState
{
    /// @brief The x-coordinate of the piece.
    int posX;

    /// @brief The y-coordinate of the piece.
    int posY;

    /// @brief The kind/shape of the piece.
    int piece;

    /// @brief The rotation of the piece.
    int rotation;
};

namespace Pieces
{
    /// @brief Return the type of a given piece.
    /// @param pieceState The state of a piece.
    /// @return Returns the following: 0 = no-block, 1 = normal block, 2 = pivot block
    int GetBlockType(const PieceState& pieceState);

    /// @brief Returns the horizontal displacement of the piece that has to be applied in
    /// order to create it in the correct position.
    /// @param piece Piece to draw
    /// @param rotation 1 of the 4 possible rotations
    /// @return Returns the horizontal displacement of the piece.
    int GetXInitialPosition(int piece, int rotation);

    /// @brief Returns the vertical displacement of the piece that has to be applied in
    /// order to create it in the correct position.
    /// @param piece Piece to draw
    /// @param rotation 1 of the 4 possible rotations
    /// @return Returns the vertical displacement of the piece.
    int GetYInitialPosition(int piece, int rotation);
};

#endif // PIECES_H
