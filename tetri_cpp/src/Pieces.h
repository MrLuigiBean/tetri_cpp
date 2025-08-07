#pragma once

#ifndef PIECES_H
#define PIECES_H

#include "PieceData.h"

/// @brief Represents a state a piece can be in.
struct PieceState
{
    /// @brief The x-coordinate of the piece.
    int posX = 0;

    /// @brief The y-coordinate of the piece.
    int posY = 0;

    /// @brief The kind/shape of the piece.
    int piece = 0;

    /// @brief The rotation of the piece.
    int rotation = 0;

    /// @brief Represents the modifications that can be made to a PieceState.
    struct IfArgs
    {
        /// @brief The desired modification to the piece's x-coordinate.
        int modPosX = 0;

        /// @brief The desired modification to the piece's y-coordinate.
        int modPosY = 0;

        /// @brief The desired modification to the piece's rotation.
        int modRotation = 0;
    };

    /// @brief Creates a new PieceState, which is a copy of this instance with modifications.
    /// @param args The modifications to apply.
    /// @return A copy of the piece with the modifications applied.
    inline PieceState If(const IfArgs& args)
    {
        return { posX + args.modPosX, posY + args.modPosY, piece,
            (rotation + args.modRotation) % TOTAL_ROTATIONS };
    }
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
