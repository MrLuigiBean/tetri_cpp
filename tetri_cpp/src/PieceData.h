#pragma once

/// @brief The total number of pieces in the game.
constexpr int TOTAL_KINDS = 7;

/// @brief The total number of rotation states of a piece.
constexpr int TOTAL_ROTATIONS = 4;

/// @brief The side length of the area representing a piece's information.
constexpr int FRAME_SIZE = 5;

/// @brief (x, y) coordinates have 2 dimensions.
constexpr int COORDINATES_DIMENSION = 2;

/// @brief A table containing tile data for each rotation of a piece.
extern char allPieceRotations[TOTAL_KINDS][TOTAL_ROTATIONS][FRAME_SIZE][FRAME_SIZE];

/// @brief A table containing the initial displacement from the board's top
/// for each rotation of a piece.
extern int allPieceInitialPositions[TOTAL_KINDS][TOTAL_ROTATIONS][COORDINATES_DIMENSION];
