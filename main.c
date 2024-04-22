#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "movegen.h"
#include "test.h"

#define DEBUG 1

void mainGameLoop(Board board);
int userMove(Board board, struct Move moves[], int *moveCount, Color color);
void botMove(Board board, struct Move moves[], int *moveCount);

int main() {
    srand(time(NULL));

    // clang-format off
    Board mainBoard = {{{2, 'R'},{2, 'N'},{2, 'B'},{2, 'Q'},{2, 'K'},{2, 'B'},{2, 'N'},{2, 'R'}}, 
                   {{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                   {{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'}},  
                   {{1, 'R'},{1, 'N'},{1, 'B'},{1, 'Q'},{1, 'K'},{1, 'B'},{1, 'N'},{1, 'R'}}};

    // clang-format on

    mainGameLoop(mainBoard);
}

void mainGameLoop(Board board) {
    struct Move userMoves[500];
    struct Move botMoves[500];
    int userMoveCount = 0;
    int botMoveCount = 0;
    Color currentPlayerColor = WHITE;
    Color userColor = WHITE;
    Color botColor = BLACK;

    while (1) {
        allValidMoves(board, userMoves, &userMoveCount, userColor);
        allValidMoves(board, botMoves, &botMoveCount, botColor);

        if (DEBUG) {
            test(board, currentPlayerColor);
            return;
        }

        printBoard(board);
        if (currentPlayerColor == userColor) {
            allValidMoves(board, userMoves, &userMoveCount, userColor);
            if (userMoveCount == 0) {
                printf("Stalemate.\n");
                return;
            }
            if (isChecked(board, botMoves, &botMoveCount, userColor, userMoves, &userMoveCount)) {
                if (isCheckmated(board, botMoves, userMoves, &botMoveCount, &userMoveCount, userColor)) {
                    printf("You lost!\n");
                    return;
                } else {
                    printf("You are checked!\n");
                }
            }
            while (!userMove(board, userMoves, &userMoveCount, userColor))
                ;
            currentPlayerColor = botColor;
            clearMoves(userMoves, &userMoveCount);
        } else {
            allValidMoves(board, botMoves, &botMoveCount, botColor);
            if (botMoveCount == 0) {
                printf("Stalemate.\n");
                return;
            }
            if (isChecked(board, userMoves, &userMoveCount, botColor, userMoves, &userMoveCount)) {
                if (isCheckmated(board, userMoves, botMoves, &userMoveCount, &botMoveCount, botColor)) {
                    printf("You Won!\n");
                    return;
                } else {
                    printf("The bot is checked!\n");
                }
            }
            botMove(board, botMoves, &botMoveCount);
            currentPlayerColor = userColor;
            clearMoves(botMoves, &botMoveCount);
        }
    }
}

// Takes in input, converts each char to a value from 0-7, and makes move
int userMove(Board board, struct Move moves[], int *moveCount, Color color) {
    char userArgs[2][3] = {"", ""};

    scanf("%s %s", userArgs[0], userArgs[1]);

    int fromRow = 56 - (int)userArgs[0][1];
    int fromCol = (int)toupper(userArgs[0][0]) - 65;

    int toRow = 56 - (int)userArgs[1][1];
    int toCol = (int)toupper(userArgs[1][0]) - 65;

    for (int i = 0; i < *moveCount; i++) {
        if (moves[i].fromRow == fromRow && moves[i].fromCol == fromCol && moves[i].toRow == toRow && moves[i].toCol == toCol) {
            makeMove(board, fromRow, fromCol, toRow, toCol);
            return 1;
        }
    }
    printf("Illegal Move\n");
    return 0;
}

// Performs random bot move
void botMove(Board board, struct Move moves[], int *moveCount) {
    int r = rand() % (*moveCount);
    makeMove(board, moves[r].fromRow, moves[r].fromCol, moves[r].toRow, moves[r].toCol);
}
