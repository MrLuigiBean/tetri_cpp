#include "Board.h"

/// @brief Initializes all board blocks to Board::POS_FREE.
Board::Board()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = POS_FREE;
}

/// @brief Store a piece in the board by filling in its blocks.
/// @param pieceState The state of a piece.
void Board::StorePiece(const PieceState& pieceState)
{
    // Store each block of the piece into the board
    for (int i1 = pieceState.posX, i2 = 0;
        i1 < pieceState.posX + PIECE_BLOCKS; i1++, i2++)
    {
        for (int j1 = pieceState.posY, j2 = 0;
            j1 < pieceState.posY + PIECE_BLOCKS; j1++, j2++)
        {
            // Store only the blocks of the piece that are not holes
            if (Pieces::GetBlockType({ j2, i2, pieceState.piece, pieceState.rotation }) != 0)
                board[i1][j1] = POS_FILLED;
        }
    }
}

/// @brief Determines if blocks have reached the top of the screen.
/// @return Returns `true` is there a blocks at the top, `false` otherwise.
bool Board::IsGameOver() const
{
    //If the first line has blocks, then, game over
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (board[i][0] == POS_FILLED)
            return true;
    }

    return false;
}

/// @brief Moves a piece to its bottom-most valid position.
/// @param pieceState The piece to drop.
void Board::DropPiece(PieceState& pieceState) const
{
    // keep going down until you hit something
    while (IsPossibleMovement(pieceState))
        pieceState.posY++;

    // go back up one space because that where the piece would actually be
    pieceState.posY--;
}

/// @brief Deletes a line of the board by moving all lines above down.
/// @param posY Vertical position of blocks in the line to delete.
void Board::DeleteLine(int posY)
{
    // Moves all the upper lines one row down
    // TODO: does this actually clear the bottom-most line? hmm...
    for (int j = posY; j > 0; j--)
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            board[i][j] = board[i][j - 1];
        }
    }
}

/// @brief Determines which lines to clear and removes them from the board.
void Board::DeletePossibleLines()
{
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int i = 0;
        for (; i < BOARD_WIDTH; ++i)
        {
            if (board[i][j] != POS_FILLED)
                break;
        }

        if (i == BOARD_WIDTH)
            DeleteLine(j);
    }
}

/// @brief Checks if the given board position is occupied.
/// @param posX The x-coordinate to check.
/// @param posY The y-coordinate to check.
/// @return `true` if the block's position is occupied, `false` otherwise.
bool Board::IsFreeBlock(int posX, int posY) const
{
    return board[posX][posY] == POS_FREE;
}

/// @brief Check if a given piece can be stored at this position on the board.
/// @param pieceState The state of a piece.
/// @return `true` if the movement is allowed, `false` otherwise.
bool Board::IsPossibleMovement(const PieceState& pieceState) const
{
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
    for (int i1 = pieceState.posX, i2 = 0;
        i1 < pieceState.posX + PIECE_BLOCKS; i1++, i2++)
    {
        for (int j1 = pieceState.posY, j2 = 0;
            j1 < pieceState.posY + PIECE_BLOCKS; j1++, j2++)
        {
            int blockType = Pieces::GetBlockType({ j2, i2, pieceState.piece, pieceState.rotation });

            // Check if the piece is outside the limits of the board
            if (i1 < 0 ||
                i1 > BOARD_WIDTH - 1 ||
                j1 > BOARD_HEIGHT - 1)
            {
                if (blockType != 0)
                    return false;
            }

            // Check if the piece has collided with a block already stored in the map
            if (j1 >= 0)
            {
                if (blockType != 0 && !IsFreeBlock(i1, j1))
                    return false;
            }
        }
    }

    // No collision
    return true;
}
