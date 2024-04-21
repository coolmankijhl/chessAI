#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "movegen.h"

void makeMove(Board board, int fromRow, int fromCol, int toRow, int toCol);
int userMove(Board board, struct Move moves[], int *moveCount);
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

    struct Move moves[500];
    int moveCount = 0;
    Color currentPlayerColor = WHITE;
    Color PlayerColor = WHITE;
    Color BotColor = BLACK;

    while (1) {
        printBoard(mainBoard);
        allValidMoves(mainBoard, moves, &moveCount, currentPlayerColor);

        if (currentPlayerColor == PlayerColor) {
            while (!userMove(mainBoard, moves, &moveCount))
                ;
            currentPlayerColor = BotColor;
        } else {
            botMove(mainBoard, moves, &moveCount);
            currentPlayerColor = PlayerColor;
        }

        clearMoves(moves, &moveCount);
    }

    for (int i = 0; i < moveCount; i++) {
        printf("(%d) %d %d -> %d %d\n", i + 1, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol);
    }
}

// Takes in input and converts values to 0-7
int userMove(Board board, struct Move moves[], int *moveCount) {
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
    return 0;
}

void botMove(Board board, struct Move moves[], int *moveCount) {
    int r = rand() % (*moveCount) - 1;
    makeMove(board, moves[r].fromRow, moves[r].fromCol, moves[r].toRow, moves[r].toCol);
}

void makeMove(Board board, int fromRow, int fromCol, int toRow, int toCol) {
    board[toRow][toCol] = board[fromRow][fromCol];

    board[fromRow][fromCol].color = NONE;
    board[fromRow][fromCol].type = EMPTY;
}

