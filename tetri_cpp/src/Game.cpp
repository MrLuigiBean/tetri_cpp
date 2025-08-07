#include "Game.h"
#include "IO.h"
#include <cstdlib>
#include <time.h>

/// @brief Constructs the board of the game using a given size.
/// @param height The height of the screen in pixels.
Game::Game(int height) : screenHeight{ height }, board{ Board(height) } {}

/// @brief Returns a random number between two integers.
/// @param a The lower end of the range.
/// @param b The upper end of the range.
/// @return A random number in the range [a, b]
int Game::GetRand(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

/// @brief Selects the first and next piece randomly.
void Game::InitGame()
{
    // Init random numbers
    srand((unsigned int)time(NULL));

    // First piece
    fallingPiece.piece = GetRand(0, 6);
    fallingPiece.rotation = GetRand(0, 3);
    fallingPiece.posX = (BOARD_WIDTH / 2) + Pieces::GetXInitialPosition(fallingPiece.piece, fallingPiece.rotation);
    fallingPiece.posY = Pieces::GetYInitialPosition(fallingPiece.piece, fallingPiece.rotation);

    // Next piece
    nextPiece.piece = GetRand(0, 6);
    nextPiece.rotation = GetRand(0, 3);
    nextPiece.posX = BOARD_WIDTH + 5;
    nextPiece.posY = 5;
}

/// @brief Sets the next piece as the current one and resets its position,
/// after which a new "next piece" is selected.
void Game::CreateNewPiece()
{
    // The new piece
    fallingPiece.piece = nextPiece.piece;
    fallingPiece.rotation = nextPiece.rotation;
    fallingPiece.posX = (BOARD_WIDTH / 2) + Pieces::GetXInitialPosition(fallingPiece.piece, fallingPiece.rotation);
    fallingPiece.posY = Pieces::GetYInitialPosition(fallingPiece.piece, fallingPiece.rotation);

    // Random next piece
    nextPiece.piece = GetRand(0, 6);
    nextPiece.rotation = GetRand(0, 3);
}

/// @brief Draws a given piece.
/// @param pieceState The state of a piece.
void Game::DrawPiece(const PieceState& pieceState) const
{
    ColorLabel col = ColorLabel::BLUE; // Color of the block

    // Obtain the position in pixel in the screen of the block we want to draw
    int pixelsX = board.GetXPosInPixels(pieceState.posX);
    int pixelsY = board.GetYPosInPixels(pieceState.posY);

    // Travel the matrix of blocks of the piece and draw the blocks that are filled
    for (int i = 0; i < PIECE_BLOCKS; i++)
    {
        for (int j = 0; j < PIECE_BLOCKS; j++)
        {
            int blockType = Pieces::GetBlockType({ j, i, pieceState.piece, pieceState.rotation });

            // Get the type of the block and draw it with the correct color
            switch (blockType)
            {
            case 1: col = GREEN; break; // For each block of the piece except the pivot
            case 2: col = BLUE; break; // For the pivot
            }

            if (blockType != 0)
                IO::DrawRectangle(pixelsX + i * BLOCK_SIZE,
                    pixelsY + j * BLOCK_SIZE,
                    (pixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                    (pixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                    col);
        }
    }
}

/// @brief Draws the board's delimiters and existing board blocks.
void Game::DrawBoard() const
{
    // Calculate the limits of the board in pixels
    int posX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int posX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int posY = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    // Check that the vertical margin is not to small
    //assert (posY > MIN_VERTICAL_MARGIN);

    // Rectangles that delimits the board
    IO::DrawRectangle(posX1 - BOARD_LINE_WIDTH, posY, posX1, screenHeight - 1, BLUE);

    IO::DrawRectangle(posX2, posY, posX2 + BOARD_LINE_WIDTH, screenHeight - 1, BLUE);

    // Check that the horizontal margin is not to small
    //assert (posX1 > MIN_HORIZONTAL_MARGIN);

    // Drawing the blocks that are already stored in the board
    posX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            // Check if the block is filled, if so, draw it
            if (!board.IsFreeBlock(i, j))
                IO::DrawRectangle(posX1 + i * BLOCK_SIZE,
                    posY + j * BLOCK_SIZE,
                    (posX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                    (posY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                    RED);
        }
    }
}

/// @brief Draws the board, the current piece and the next piece.
void Game::DrawScene()
{
    DrawBoard(); // Draw the delimitation lines and blocks stored in the board
    DrawPiece(fallingPiece); // Draw the playing piece
    DrawPiece(nextPiece); // Draw the next piece
}
