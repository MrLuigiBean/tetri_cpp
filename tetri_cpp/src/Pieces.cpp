#include "Pieces.h"
#include "PieceData.h"

/// @brief Return the type of a given piece.
/// @param piece The kind of piece to check.
/// @param rotation The piece's rotation state.
/// @param posX The x position to query.
/// @param posY The y position to query.
/// @return Returns the following: 0 = no-block, 1 = normal block, 2 = pivot block
int Pieces::GetBlockType(int piece, int rotation, int posX, int posY)
{
    return mPieces[piece][rotation][posX][posY];
}

/// @brief Returns the horizontal displacement of the piece that has to be applied in
/// order to create it in the correct position.
/// @param piece Piece to draw
/// @param rotation 1 of the 4 possible rotations
/// @return Returns the horizontal displacement of the piece.
int Pieces::GetXInitialPosition(int piece, int rotation)
{
    return mPiecesInitialPosition[piece][rotation][0];
}

/// @brief Returns the vertical displacement of the piece that has to be applied in
/// order to create it in the correct position.
/// @param piece Piece to draw
/// @param rotation 1 of the 4 possible rotations
/// @return Returns the vertical displacement of the piece.
int Pieces::GetYInitialPosition(int piece, int rotation)
{
    return mPiecesInitialPosition[piece][rotation][1];
}
