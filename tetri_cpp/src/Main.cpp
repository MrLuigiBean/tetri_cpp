#ifndef LINUX
#include <windows.h>
#endif

#ifndef LINUX
#include "SDL3/SDL.h"
// #include "SDL3/SDL_GfxPrimitives/SDL_gfxPrimitives.h"
#else
#include <SDL/SDL.h>
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"
#endif
// #pragma comment (lib, "SDL3/lib/SDL.lib")
// #pragma comment (lib, "SDL3/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

#include "Game.h"

/*
==================
Main
==================
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    static_cast<void>(hInstance);
    static_cast<void>(hPrevInstance);
    static_cast<void>(lpCmdLine);
    static_cast<void>(nCmdShow);

    // -- Vars --

    // Class for drawing staff, it uses SDL for the rendering. Change the methods of this class
    // in order to use a different renderer
    IO mIO;
    int mScreenHeight = mIO.GetScreenHeight();

    // Pieces
    Pieces mPieces;

    // Board
    Board mBoard(&mPieces, mScreenHeight);

    // Game
    Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

    // Get the actual clock milliseconds (SDL)
    unsigned long mTime1 = static_cast<unsigned long>(SDL_GetTicks());

    // This is the main loop.We can exit by pressing ESC.In each frame we clear
    // and update the screen and draw everything.

    // -- Main Loop --

    while (!mIO.IsKeyDown(SDLK_ESCAPE))
    {
        // -- Draw --

        mIO.ClearScreen(); // Clear screen
        mGame.DrawScene(); // Draw staff
        mIO.UpdateScreen(); // Put the graphic context in the screen

        // We start with the input.If we press left, down or right we try to move the
        // piece in that directions.We only move the piece if the movement is possible.

        // -- Input --

        int mKey = mIO.Pollkey();

        switch (mKey)
        {
        case (SDLK_RIGHT):
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX++;
            break;
        }

        case (SDLK_LEFT):
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX--;
            break;
        }

        case (SDLK_DOWN):
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
                mGame.mPosY++;
            break;
        }

        // By pressing `x`, the piece will fall down directly to the ground.
        // This is really easy to implement by trying to move the piece down until 
        // the movement is not possible.Then we store the piece, delete possible lines 
        // and check out if the game is over, if not, we create a new piece.

        case (SDLK_X):
        {
            // Check collision from up to down
            while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

            mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

            mBoard.DeletePossibleLines();

            if (mBoard.IsGameOver())
            {
                mIO.Getkey();
                exit(0);
            }

            mGame.CreateNewPiece();

            break;
        }

        // By pressing `z` we rotate the piece.With the methods that we have already
        // implement this is an easy task.The rotation is in fact to change to the
        // next rotated stored piece.We first should check that the rotated piece will
        // be drawn without colliding, if so, we sets this rotation as the current one.

        case (SDLK_Z):
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
                mGame.mRotation = (mGame.mRotation + 1) % 4;

            break;
        }
        }

        // If WAIT_TIME passed, the piece should fall down one block.We have to check
        // out if the movement is possible, if not, the piece should be stored and we
        // have to check if we can delete lines.We also see if the game is over, if
        // not, we create a new piece.

        // -- Vertical movement --

        unsigned long mTime2 = static_cast<unsigned long>(SDL_GetTicks());

        if ((mTime2 - mTime1) > WAIT_TIME)
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
            {
                mGame.mPosY++;
            }
            else
            {
                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

                mBoard.DeletePossibleLines();

                if (mBoard.IsGameOver())
                {
                    mIO.Getkey();
                    exit(0);
                }

                mGame.CreateNewPiece();
            }

            mTime1 = static_cast<unsigned long>(SDL_GetTicks());
        }
    }

    return 0;
}
