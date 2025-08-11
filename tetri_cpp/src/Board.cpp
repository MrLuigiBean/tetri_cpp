#include "Board.h"

/// @brief Initializes all board blocks to Board::POS_FREE.
Board::Board()
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
        for (int col = 0; col < BOARD_WIDTH; col++)
            board[row][col] = POS_FREE;
}

/// @brief Store a piece in the board by filling in its blocks.
/// @param pieceState The state of a piece.
void Board::StorePiece(const PieceState& pieceState)
{
    // Store each block of the piece into the board
    for (int row = pieceState.posY, matrixRow = 0;
        row < pieceState.posY + PIECE_BLOCKS; row++, matrixRow++)
    {
        for (int col = pieceState.posX, matrixCol = 0;
            col < pieceState.posX + PIECE_BLOCKS; col++, matrixCol++)
        {
            // Store only the blocks of the piece that are not holes
            if (Pieces::GetBlockType({ matrixCol, matrixRow, pieceState.piece, pieceState.rotation }) != 0)
                board[row][col] = POS_FILLED;
        }
    }
}

/// @brief Determines if blocks have reached the top of the screen.
/// @return Returns `true` is there a blocks at the top, `false` otherwise.
bool Board::IsGameOver() const
{
    // If the first line has blocks, then game over
    for (int col = 0; col < BOARD_WIDTH; col++)
    {
        if (board[0][col] == POS_FILLED)
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
    for (int row = posY; row > 0; row--)
        for (int col = 0; col < BOARD_WIDTH; col++)
            board[row][col] = board[row - 1][col];
}

/// @brief Determines which lines to clear and removes them from the board.
void Board::DeletePossibleLines()
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        bool isRowFull = true;
        for (int col = 0; col < BOARD_WIDTH; ++col)
        {
            isRowFull &= board[row][col] == POS_FILLED;
            if (!isRowFull)
                break;
        }

        if (isRowFull)
            DeleteLine(row);
    }
}

/// @brief Checks if the given board position is occupied.
/// @param posX The x-coordinate to check.
/// @param posY The y-coordinate to check.
/// @return `true` if the block's position is occupied, `false` otherwise.
bool Board::IsFreeBlock(int posX, int posY) const
{
    return board[posY][posX] == POS_FREE;
}

/// @brief Check if a given piece can be stored at this position on the board.
/// @param pieceState The state of a piece.
/// @return `true` if the movement is allowed, `false` otherwise.
bool Board::IsPossibleMovement(const PieceState& pieceState) const
{
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
    for (int row = pieceState.posY, matrixRow = 0;
        row < pieceState.posY + PIECE_BLOCKS; row++, matrixRow++)
    {
        for (int col = pieceState.posX, matrixCol = 0;
            col < pieceState.posX + PIECE_BLOCKS; col++, matrixCol++)
        {
            int blockType = Pieces::GetBlockType({ matrixCol, matrixRow, pieceState.piece, pieceState.rotation });

            // Check if the piece is outside the limits of the board
            if (col < 0 ||
                col > BOARD_WIDTH - 1 ||
                row > BOARD_HEIGHT - 1)
            {
                if (blockType != 0)
                    return false;
            }

            // Check if the piece has collided with a block already stored in the map
            if (row >= 0)
            {
                if (blockType != 0 && !IsFreeBlock(col, row))
                    return false;
            }
        }
    }

    // No collision
    return true;
}
