#ifndef movegen_h
#define movegen_h

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "board.h"

struct Move
{
        uint8_t fromRow;
        uint8_t fromCol;
        uint8_t toRow;
        uint8_t toCol;
};

void clearMoves(struct Move moves[], int *moveCount);
void allValidMoves(Board board, struct Move moves[], int *moveCOunt, Color color);
bool isEnemy(Board board, int y, int x, Color color);
bool isInBounds(int y, int x);
void validPawnMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validKnightMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validRookMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validBishopMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validQueenMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validKingMoves(Board board, struct Move moves[], int *moveCount, Color color);

#endif

