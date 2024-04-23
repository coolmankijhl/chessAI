#ifndef board_h
#define board_h

#include <stdbool.h>
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
    bool castleRights;
} Piece;

struct historyNode {
    bool castled;
    int castleRow;
    int castleCol;
    PieceType typeTaken;
    Color colorTaken;
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

typedef Piece Board[8][8];

void printBoard(Board board);
void makeMove(Board board, int fromRow, int fromCol, int toRow, int toCol);
void undoMove(Board board, Color playerColor);

#endif
