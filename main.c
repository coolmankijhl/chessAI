#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

#include "board.h"
#include "engine.h"
#include "movegen.h"
#include "test.h"

void mainGameLoop(Board board);
int userMove(Board board, struct Move moves[], int *moveCount, Color color);
void botMove(Board board, struct Move moves[], int *moveCount, Color currentPlayerColor);
void isThereUserPromotion(Board board, Color userColor);

int main() {
    srand(time(NULL));

    // clang-format off
    Board mainBoard = {{{2, 'R', true},{2, 'N'},{2, 'B'},{2, 'Q'},{2, 'K', true},{2, 'B'},{2, 'N'},{2, 'R', true}}, 
                   {{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                   {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                   {{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'}},  
                   {{1, 'R', true},{1, 'N'},{1, 'B'},{1, 'Q'},{1, 'K', true},{1, 'B'},{1, 'N'},{1, 'R', true}}};

         Board testBoard = {{{2, 'R', true},{0, '_'},{0, '_'},{0, '_'},{2, 'K', true},{0, '_'},{0, '_'},{2, 'R', true}},
                             {{0, '_'},{0, '_'},{0, '_'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{0, '_'}},
                             {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                             {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                             {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                             {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                             {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'P'},{0, '_'}},
                             {{1, 'R',true},{2, 'P'},{0, '_'},{0, '_'},{1, 'K',true},{2, 'P'},{0, '_'},{1, 'R',true}}};

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

        if (DEBUG) {
            allValidMoves(board, userMoves, &userMoveCount, botMoves, &botMoveCount, userColor, botColor);
            test(currentPlayerColor);
            return;
        }

        printBoard(board);
        if (currentPlayerColor == userColor) {
            allValidMoves(board, userMoves, &userMoveCount, botMoves, &botMoveCount, userColor, botColor);
            if (isCheckmate(board))
                return;
            if (userMoveCount == 0) {
                printf("Stalemate.\n");
                return;
            }
            while (!userMove(board, userMoves, &userMoveCount, userColor))
                ;
            currentPlayerColor = botColor;
            clearMoves(userMoves, &userMoveCount);
        } else {
            allValidMoves(board, botMoves, &botMoveCount, userMoves, &userMoveCount, botColor, userColor);
            if (isCheckmate(board))
                return;
            if (botMoveCount == 0) {
                printf("Stalemate.\n");
                return;
            }
            botMove(board, botMoves, &botMoveCount, currentPlayerColor);
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
            makeMove(board, fromRow, fromCol, toRow, toCol, false);
            isThereUserPromotion(board, color);
            return 1;
        }
    }
    printf("Illegal Move\n");
    return 0;
}

void isThereUserPromotion(Board board, Color userColor) {
    int promotion = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == PAWN && ((row == 7 && userColor == BLACK) || (row == 0 && userColor == WHITE))) {
                do {
                    printf("Please pick the promotion for your pawn! 1.Queen, 2.Rook, 3.Bishop, 4.Knight\n");
                    scanf("%d", &promotion);
                } while (promotion < 1 && promotion > 4);

                switch (promotion) {
                case (1):
                    board[row][col].type = QUEEN;
                    break;
                case (2):
                    board[row][col].type = ROOK;
                    break;
                case (3):
                    board[row][col].type = BISHOP;
                    break;
                case (4):
                    board[row][col].type = KNIGHT;
                    break;
                }
            }
        }
    }
}

void botMove(Board board, struct Move moves[], int *moveCount, Color currentPlayerColor) {
    struct Move bestMove = findBestMove(board, 7, currentPlayerColor);
    makeMove(board, bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol, true);
}

