#pragma once

#ifndef PIECES_H
#define PIECES_H

namespace Pieces
{
    /// @brief Return the type of a given piece.
    /// @param piece The kind of piece to check.
    /// @param rotation The piece's rotation state.
    /// @param posX The x position to query.
    /// @param posY The y position to query.
    /// @return Returns the following: 0 = no-block, 1 = normal block, 2 = pivot block
    int GetBlockType(int piece, int rotation, int posX, int posY);

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
