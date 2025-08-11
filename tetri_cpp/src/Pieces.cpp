#include "Pieces.h"
#include "PieceData.h"

/// @brief Return the type of a given piece.
/// @param pieceState The state of a piece.
/// @return Returns the following: 0 = no-block, 1 = normal block, 2 = pivot block
int Pieces::GetBlockType(const PieceState& pieceState)
{
    return allPieceRotations[pieceState.piece][pieceState.rotation]
        [pieceState.posY][pieceState.posX];
}

/// @brief Returns the horizontal displacement of the piece that has to be applied in
/// order to create it in the correct position.
/// @param piece Piece to draw
/// @param rotation 1 of the 4 possible rotations
/// @return Returns the horizontal displacement of the piece.
int Pieces::GetXInitialPosition(int piece, int rotation)
{
    return allPieceInitialPositions[piece][rotation][0];
}

/// @brief Returns the vertical displacement of the piece that has to be applied in
/// order to create it in the correct position.
/// @param piece Piece to draw
/// @param rotation 1 of the 4 possible rotations
/// @return Returns the vertical displacement of the piece.
int Pieces::GetYInitialPosition(int piece, int rotation)
{
    return allPieceInitialPositions[piece][rotation][1];
}
