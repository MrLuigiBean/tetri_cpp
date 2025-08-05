#pragma once

#ifndef PIECES_H
#define PIECES_H

// ---------------------------
// Pieces
// ---------------------------

class Pieces
{
public:

    static int GetBlockType(int pPiece, int pRotation, int pX, int pY);
    static int GetXInitialPosition(int pPiece, int pRotation);
    static int GetYInitialPosition(int pPiece, int pRotation);
};

#endif // PIECES_H
