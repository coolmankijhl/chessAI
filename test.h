// Includes testcases from https://www.chessprogramming.org/Perft_Results

#include <stdbool.h>
#include <unistd.h>

#include "board.h"
#include "movegen.h"

#define PRINT_BOARD true
#define BOARD1 false
#define BOARD2 false
#define BOARD3 false
#define BOARD4 false
#define BOARD5 false
#define BOARD6 false

// Recursivly debugs piece moves
int perft(int depth, Board board, Color currentPlayerColor) {
    if (depth == 0) {
        return 1; // Leaf node
    }

    int totalNodes = 0;

    struct Move moves[10000];
    int moveCount = 0;

    Board boardCopy;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            boardCopy[row][col] = board[row][col];
        }
    }
    allValidMoves(boardCopy, moves, NULL, &moveCount, currentPlayerColor);

    if (PRINT_BOARD) {
        sleep(1);
        printBoard(board);
    }

    for (int i = 0; i < moveCount; i++) {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                boardCopy[row][col] = board[row][col];
            }
        }
        makeMove(boardCopy, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, moves[i].isEnPassant);
        // printBoard(boardCopy);
        if (!isChecked(boardCopy, moves, &moveCount, currentPlayerColor)) {
            Color nextPlayerColor = (currentPlayerColor == WHITE) ? BLACK : WHITE;
            totalNodes += perft(depth - 1, boardCopy, nextPlayerColor);
        }
        undoMove(boardCopy, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol); // Undo the move after exploring it
    }

    return totalNodes;
}

void test(Board board, Color currentPlayerColor) {
    // clang-format off
      Board board1 = {{{2, 'R', true},{2, 'N'},{2, 'B'},{2, 'Q'},{2, 'K', true},{2, 'B'},{2, 'N'},{2, 'R', true}},
                     {{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'}},
                     {{1, 'R', true},{1, 'N'},{1, 'B'},{1, 'Q'},{1, 'K', true},{1, 'B'},{1, 'N'},{1, 'R', true}}};
  
     Board board2 = {{{2, 'R', true},{0, '_'},{0, '_'},{0, '_'},{2, 'K', true},{0, '_'},{0, '_'},{2, 'R', true}},
                         {{2, 'P'},{0, '_'},{2, 'P'},{2, 'P'},{2, 'Q'},{2, 'P'},{2, 'B'},{0, '_'}},
                         {{2, 'B'},{2, 'N'},{0, '_'},{0, '_'},{2, 'P'},{2, 'N'},{2, 'P'},{0, '_'}},
                         {{0, '_'},{0, '_'},{0, '_'},{1, 'P'},{1, 'N'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'},{1, 'Q'},{0, '_'},{2, 'P'}},
                         {{1, 'P'},{1, 'P'},{1, 'P'},{1, 'B'},{1, 'B'},{1, 'P'},{1, 'P'},{1, 'P'}},
                         {{1, 'R', true},{0, '_'},{0, '_'},{0, '_'},{1, 'K', true},{0, '_'},{0, '_'},{1, 'R', true}}};
  
  
      Board board3 =  {{{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{1, 'K'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{2, 'R'}},
                          {{0, '_'},{1, 'R'},{0, '_'},{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{2, 'K'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'P'},{0, '_'},{1, 'P'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}};
  
      Board board4 = {{{2, 'R', true},{0, '_'},{0, '_'},{0, '_'},{2, 'K', true},{0, '_'},{0, '_'},{2, 'R', true}},
                         {{1, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{0, '_'},{2, 'P'},{2, 'P'},{2, 'P'}},
                         {{0, '_'},{2, 'B'},{0, '_'},{0, '_'},{0, '_'},{2, 'N'},{2, 'B'},{1, 'N'}},
                         {{2, 'N'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{1, 'B'},{1, 'B'},{1, 'P'},{0, '_'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'}},
                         {{2, 'Q'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'}},
                         {{1, 'P'},{2, 'P'},{0, '_'},{1, 'P'},{0, '_'},{0, '_'},{1, 'P'},{1, 'P'}},
                         {{1, 'R', true},{0, '_'},{0, '_'},{1, 'Q'},{0, '_'},{1, 'R'},{1, 'K'},{0, '_'}}};
  
       Board board5 = {{{2, 'R', true},{2, 'N'},{2, 'B'},{2, 'Q'},{0, '_'},{2, 'K'},{0, '_'},{2, 'R', true}},
                         {{2, 'P'},{2, 'P'},{0, '_'},{1, 'P'},{1, 'B'},{1, 'P'},{1, 'P'},{1, 'P'}},
                         {{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{1, 'B'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{1, 'P'},{1, 'P'},{1, 'P'},{0, '_'},{1, 'N'},{2, 'N'},{1, 'P'},{1, 'P'}},
                         {{1, 'R'},{1, 'N'},{1, 'B'},{1, 'Q'},{1, 'K'},{0, '_'},{0, '_'},{1, 'R', true}}};
  
      Board board6 = {{{2, 'R', true},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{2, 'R', false},{2, 'R', false},{0, '_'}},
                         {{0, '_'},{2, 'P'},{2, 'P'},{0, '_'},{2, 'Q'},{2, 'P'},{2, 'P'},{2, 'P'}},
                         {{2, 'P'},{0, '_'},{2, 'N'},{2, 'P'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{2, 'B'},{0, '_'},{2, 'P'},{0, '_'},{1, 'B'},{0, '_'}},
                         {{0, '_'},{0, '_'},{1, 'B'},{0, '_'},{1, 'P'},{0, '_'},{2, 'B'},{0, '_'}},
                         {{1, 'P'},{0, '_'},{1, 'N'},{1, 'P'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'}},
                         {{0, '_'},{1, 'P'},{1, 'P'},{0, '_'},{1, 'Q'},{1, 'P'},{1, 'P'},{1, 'P'}},
                         {{1, 'R'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'R'},{1, 'K'},{0, '_'}}};

    // clang-format on
    if (BOARD1) {
        printf("(%d) %d\n", perft(1, board, currentPlayerColor) == 20, perft(1, board, currentPlayerColor));
        printf("(%d) %d\n", perft(2, board, currentPlayerColor) == 400, perft(2, board, currentPlayerColor));
        printf("(%d) %d\n\n", perft(3, board, currentPlayerColor) == 8902, perft(3, board, currentPlayerColor));
    }
    if (BOARD2) {
        printf("(%d) %d\n", perft(1, board2, currentPlayerColor) == 48, perft(1, board2, currentPlayerColor));
        printf("(%d) %d\n", perft(2, board2, currentPlayerColor) == 2039, perft(2, board2, currentPlayerColor));
        printf("(%d) %d\n\n", perft(3, board2, currentPlayerColor) == 97862, perft(3, board2, currentPlayerColor));
    }
    if (BOARD3) {
        printf("(%d) %d\n", perft(1, board3, currentPlayerColor) == 14, perft(1, board3, currentPlayerColor));
        printf("(%d) %d\n", perft(2, board3, currentPlayerColor) == 191, perft(2, board3, currentPlayerColor));
        printf("(%d) %d\n\n", perft(3, board3, currentPlayerColor) == 2812, perft(3, board3, currentPlayerColor));
    }
    if (BOARD4) {
        printf("(%d) %d\n", perft(1, board4, currentPlayerColor) == 6, perft(1, board4, currentPlayerColor));
        printf("(%d) %d\n", perft(2, board4, currentPlayerColor) == 264, perft(2, board4, currentPlayerColor));
        printf("(%d) %d\n\n", perft(3, board4, currentPlayerColor) == 9467, perft(3, board4, currentPlayerColor));
    }
    if (BOARD5) {
        printf("(%d) %d\n", perft(1, board5, currentPlayerColor) == 44, perft(1, board5, currentPlayerColor));
        printf("(%d) %d\n", perft(2, board5, currentPlayerColor) == 1486, perft(2, board5, currentPlayerColor));
        printf("(%d) %d\n\n", perft(3, board5, currentPlayerColor) == 62379, perft(3, board5, currentPlayerColor));
    }
    if (BOARD6) {
        printf("(%d) %d\n", perft(1, board6, currentPlayerColor) == 1, perft(1, board6, currentPlayerColor));
        printf("(%d) %d\n", perft(2, board6, currentPlayerColor) == 46, perft(2, board6, currentPlayerColor));
        printf("(%d) %d\n\n", perft(3, board6, currentPlayerColor) == 2079, perft(3, board6, currentPlayerColor));
    }
}

