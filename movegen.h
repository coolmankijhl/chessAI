#ifndef movegen_h
#define movegen_h

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

struct Move {
    uint8_t fromRow;
    uint8_t fromCol;
    uint8_t toRow;
    uint8_t toCol;
    bool isEnPassant;
};

void clearMoves(struct Move moves[], int *moveCount);
void allValidMoves(Board board, struct Move moves[], struct Move enemyMoves[], int *moveCount, Color color);
bool isEnemy(Board board, int y, int x, Color color);
bool isInBounds(int y, int x);
void validPawnMoves(Board board, struct Move moves[], struct Move enemyMoves[], int *moveCount, Color color);
void validKnightMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validRookMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validBishopMoves(Board board, struct Move moves[], int *moveCount, Color color);
void validQueenMoves(Board board, struct Move moves[], int *moveCount, Color color);
bool validKingMoves(Board board, struct Move moves[], int *moveCount, Color color);
void isThereUserPromotion(Board board, Color color);
void isThereBotPromotion(Board board, Color color);
bool isUnderAttack(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color defenderColor, int squareRow, int squareCol);
bool isChecked(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color defenderColor);
bool isCheckmated(Board board, struct Move attackerMoves[], struct Move defenderMoves[], int *attackerMoveCount, int *defenderMoveCount, Color defenderColor);

#endif

