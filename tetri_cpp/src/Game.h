#pragma once
#ifndef GAME_H
#define GAME_H

// -- Includes --

#include "Board.h"

constexpr int WAIT_TIME = 700; // Number of milliseconds that the piece remains before going 1 block down */

// ---------------------------
// Game
// ---------------------------

class Game
{
public:

    Game(int pScreenHeight);

    void DrawScene();
    void CreateNewPiece();

    Board board;
    int mPosX = 0, mPosY = 0; // Position of the piece that is falling down
    int mPiece = 0, mRotation = 0; // Kind and rotation the piece that is falling down

private:

    int mScreenHeight = 0; // Screen height in pixels
    int mNextPosX = 0, mNextPosY = 0; // Position of the next piece
    int mNextPiece = 0, mNextRotation = 0; // Kind and rotation of the next piece

    int GetRand(int pA, int pB);
    void InitGame();
    void DrawPiece(int pX, int pY, int pPiece, int pRotation);
    void DrawBoard();
};

#endif // GAME_H
