#ifndef board_h
#define board_h

#include <stdio.h>

#define BOARD_SIZE 8

typedef enum {
    PAWN = 'P',
    KNIGHT = 'N',
    BISHOP = 'B',
    ROOK = 'R',
    QUEEN = 'Q',
    KING = 'K',
    EMPTY = '_'
} PieceType;

typedef enum {
    NONE,  // 0
    WHITE, // 1
    BLACK  // 2
} Color;

typedef struct {
    Color color;
    PieceType type;
} Piece;

typedef Piece Board[8][8];

void printBoard(Board board);

#endif
