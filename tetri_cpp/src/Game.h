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

    Game(Board* pBoard, int pScreenHeight);

    void DrawScene();
    void CreateNewPiece();

    int mPosX, mPosY; // Position of the piece that is falling down
    int mPiece, mRotation; // Kind and rotation the piece that is falling down

private:

    int mScreenHeight; // Screen height in pixels
    int mNextPosX, mNextPosY; // Position of the next piece
    int mNextPiece, mNextRotation; // Kind and rotation of the next piece

    Board* mBoard;

    int GetRand(int pA, int pB);
    void InitGame();
    void DrawPiece(int pX, int pY, int pPiece, int pRotation);
    void DrawBoard();
};

#endif // GAME_H
