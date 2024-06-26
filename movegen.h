#ifndef movegen_h
#define movegen_h

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

struct Move {
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

void clearMoves(struct Move moves[], int *moveCount);
void allValidMoves(Board board, struct Move moves[], int *moveCount, struct Move enemyMoves[], int *enemyMoveCount, Color color, Color enemyColor);
bool isEnemy(Board board, int y, int x, Color color);
bool isInBounds(int y, int x);
void validPawnMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validKnightMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validRookMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validBishopMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validQueenMoves(Board board, struct Move moves[], int *moveCount, Color color);
bool validKingMoves(Board board, struct Move moves[], int *moveCount, Color color);
bool isUnderAttack(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color defenderColor, int squareRow, int squareCol);
bool isCheck(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color playerColor);
bool isCheckmate(Board board);

#endif

