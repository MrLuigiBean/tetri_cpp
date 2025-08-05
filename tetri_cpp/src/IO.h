#pragma once
#ifndef IO_H
#define IO_H

// -- Enums --

enum color { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX }; // Colors

// ---------------------------
// IO
// ---------------------------

class IO
{
public:

    IO();

    void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
    void ClearScreen();
    int GetScreenHeight();
    int InitGraph();
    int Pollkey();
    int Getkey();
    int IsKeyDown(int pKey);
    void UpdateScreen();

};

#endif // IO_H
