#include "Board.h"

/// @brief Initialises the board with a given height.
/// @param height The height of the board in pixels.
Board::Board(int height) : boardHeight{ height } {}

/// @brief Initializes all board blocks to Board::POS_FREE.
void Board::InitBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = POS_FREE;
}

/// @brief Store a piece in the board by filling in its blocks.
/// @param posX The x-coordinate of the piece.
/// @param posY The y-coordinate of the piece.
/// @param piece The kind of the piece.
/// @param rotation The rotation of the piece.
void Board::StorePiece(int posX, int posY, int piece, int rotation)
{
    // Store each block of the piece into the board
    for (int i1 = posX, i2 = 0; i1 < posX + PIECE_BLOCKS; i1++, i2++)
    {
        for (int j1 = posY, j2 = 0; j1 < posY + PIECE_BLOCKS; j1++, j2++)
        {
            // Store only the blocks of the piece that are not holes
            if (Pieces::GetBlockType({ j2, i2, piece, rotation }) != 0)
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
        // TODO: This is just a for loop bro...
        int i = 0;
        while (i < BOARD_WIDTH)
        {
            if (board[i][j] != POS_FILLED)
                break;
            i++;
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

/// @brief Returns the given horizontal coordinate in pixels.
/// @param posX The x-coordinate of the block.
/// @return Returns the horizontal position in pixels.
int Board::GetXPosInPixels(int posX) const
{
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (posX * BLOCK_SIZE));
}

/// @brief Returns the given vertical coordinate in pixels.
/// @param posY The y-coordinate of the block.
/// @return Returns the vertical position in pixels.
int Board::GetYPosInPixels(int posY) const
{
    return ((boardHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (posY * BLOCK_SIZE));
}

/// @brief Check if a given piece can be stored at this position on the board.
/// @param posX The x-coordinate of the position to check.
/// @param posY The y-coordinate of the position to check.
/// @param piece The kind of piece.
/// @param rotation The rotation of the piece.
/// @return `true` if the movement is allowed, `false` otherwise.
bool Board::IsPossibleMovement(int posX, int posY, int piece, int rotation) const
{
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
    for (int i1 = posX, i2 = 0; i1 < posX + PIECE_BLOCKS; i1++, i2++)
    {
        for (int j1 = posY, j2 = 0; j1 < posY + PIECE_BLOCKS; j1++, j2++)
        {
            int blockType = Pieces::GetBlockType({ j2, i2, piece, rotation });

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
