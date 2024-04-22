// Includes testcases from https://www.chessprogramming.org/Perft_Results

#include <stdbool.h>
#include <unistd.h>

#include "board.h"
#include "movegen.h"

#define PRINT_BOARD 0
#define PRINT_BOARD_DELAY 1
#define PRINT_BOARD_DELAY_TIME 1
#define PRINT_MOVE 0
#define BOARD1 1
#define BOARD2 1
#define BOARD3 1
#define BOARD4 1
#define BOARD5 1
#define BOARD6 1
#define TESTBOARD 0

int perft(int depth, Board board, Color currentPlayerColor) {
    struct Move moves[10000];
    int moveCount = 0;
    struct Move enemyMoves[10000];
    int enemyMoveCount = 0;

    allValidMoves(board, moves, &moveCount, currentPlayerColor);
    allValidMoves(board, enemyMoves, &enemyMoveCount, (currentPlayerColor == WHITE) ? BLACK : WHITE);

    if (depth == 0 || isCheckmated(board, enemyMoves, moves, &enemyMoveCount, &moveCount, currentPlayerColor)) {
        return 1; // Leaf node or checkmate
    }

    int totalNodes = 0;

    if (PRINT_BOARD) {
        if (PRINT_BOARD_DELAY) {
            sleep(PRINT_BOARD_DELAY_TIME);
        }
        printBoard(board);
    }

    for (int i = 0; i < moveCount; i++) {
        makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol);

        if (PRINT_MOVE) {
            printf("%d, %d -> %d, %d\n", moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol);
            if (!isInBounds(moves[i].fromRow, moves[i].fromCol) || !isInBounds(moves[i].toRow, moves[i].toCol)) {
                exit(0);
            }
        }

        Color nextPlayerColor = (currentPlayerColor == WHITE) ? BLACK : WHITE;
        totalNodes += perft(depth - 1, board, nextPlayerColor);
        undoMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol);
    }

    return totalNodes;
}

void test(Board board, Color currentPlayerColor) {
    // clang-format off
      Board board1 = {{{2, 'R'},{2, 'N'},{2, 'B'},{2, 'Q'},{2, 'K'},{2, 'B'},{2, 'N'},{2, 'R'}},
                     {{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{2, 'P'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                     {{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'},{1, 'P'}},
                     {{1, 'R'},{1, 'N'},{1, 'B'},{1, 'Q'},{1, 'K'},{1, 'B'},{1, 'N'},{1, 'R'}}};
  
     Board board2 = {{{2, 'R'},{0, '_'},{0, '_'},{0, '_'},{2, 'K'},{0, '_'},{0, '_'},{2, 'R'}},
                         {{2, 'P'},{0, '_'},{2, 'P'},{2, 'P'},{2, 'Q'},{2, 'P'},{2, 'B'},{0, '_'}},
                         {{2, 'B'},{2, 'N'},{0, '_'},{0, '_'},{2, 'P'},{2, 'N'},{2, 'P'},{0, '_'}},
                         {{0, '_'},{0, '_'},{0, '_'},{1, 'P'},{1, 'N'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'},{1, 'Q'},{0, '_'},{2, 'P'}},
                         {{1, 'P'},{1, 'P'},{1, 'P'},{1, 'B'},{1, 'B'},{1, 'P'},{1, 'P'},{1, 'P'}},
                         {{1, 'R'},{0, '_'},{0, '_'},{0, '_'},{1, 'K'},{0, '_'},{0, '_'},{1, 'R'}}};
  
  
      Board board3 =  {{{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{1, 'K'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{2, 'R'}},
                          {{0, '_'},{1, 'R'},{0, '_'},{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{2, 'K'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'P'},{0, '_'},{1, 'P'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}};
  
      Board board4 = {{{2, 'R'},{0, '_'},{0, '_'},{0, '_'},{2, 'K'},{0, '_'},{0, '_'},{2, 'R'}},
                         {{1, 'P'},{2, 'P'},{2, 'P'},{2, 'P'},{0, '_'},{2, 'P'},{2, 'P'},{2, 'P'}},
                         {{0, '_'},{2, 'B'},{0, '_'},{0, '_'},{0, '_'},{2, 'N'},{2, 'B'},{1, 'N'}},
                         {{2, 'N'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{1, 'B'},{1, 'B'},{1, 'P'},{0, '_'},{1, 'P'},{0, '_'},{0, '_'},{0, '_'}},
                         {{2, 'Q'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'}},
                         {{1, 'P'},{2, 'P'},{0, '_'},{1, 'P'},{0, '_'},{0, '_'},{1, 'P'},{1, 'P'}},
                         {{1, 'R'},{0, '_'},{0, '_'},{1, 'Q'},{0, '_'},{1, 'R'},{1, 'K'},{0, '_'}}};
  
       Board board5 = {{{2, 'R'},{2, 'N'},{2, 'B'},{2, 'Q'},{0, '_'},{2, 'K'},{0, '_'},{2, 'R'}},
                         {{2, 'P'},{2, 'P'},{0, '_'},{1, 'P'},{1, 'B'},{1, 'P'},{1, 'P'},{1, 'P'}},
                         {{0, '_'},{0, '_'},{2, 'P'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{1, 'B'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                         {{1, 'P'},{1, 'P'},{1, 'P'},{0, '_'},{1, 'N'},{2, 'N'},{1, 'P'},{1, 'P'}},
                         {{1, 'R'},{1, 'N'},{1, 'B'},{1, 'Q'},{1, 'K'},{0, '_'},{0, '_'},{1, 'R'}}};
  
      Board board6 = {{{2, 'R'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{2, 'R'},{2, 'R'},{0, '_'}},
                         {{0, '_'},{2, 'P'},{2, 'P'},{0, '_'},{2, 'Q'},{2, 'P'},{2, 'P'},{2, 'P'}},
                         {{2, 'P'},{0, '_'},{2, 'N'},{2, 'P'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'}},
                         {{0, '_'},{0, '_'},{2, 'B'},{0, '_'},{2, 'P'},{0, '_'},{1, 'B'},{0, '_'}},
                         {{0, '_'},{0, '_'},{1, 'B'},{0, '_'},{1, 'P'},{0, '_'},{2, 'B'},{0, '_'}},
                         {{1, 'P'},{0, '_'},{1, 'N'},{1, 'P'},{0, '_'},{1, 'N'},{0, '_'},{0, '_'}},
                         {{0, '_'},{1, 'P'},{1, 'P'},{0, '_'},{1, 'Q'},{1, 'P'},{1, 'P'},{1, 'P'}},
                         {{1, 'R'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{1, 'R'},{1, 'K'},{0, '_'}}};
      
      Board testBoard = {{{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}}, 
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'},{0, '_'}},
                          {{0, '_',},{0, '_'},{0, '_'},{0, '_'},{1, 'K'},{0, '_'},{0, '_'},{0, '_',}}};

    // clang-format on
    if (BOARD1) {
        printf("(%d) %d = 20\n", perft(1, board, currentPlayerColor) == 20, perft(1, board, currentPlayerColor));
        printf("(%d) %d = 400\n", perft(2, board, currentPlayerColor) == 400, perft(2, board, currentPlayerColor));
        printf("(%d) %d = 8902\n", perft(3, board, currentPlayerColor) == 8902, perft(3, board, currentPlayerColor));
        printf("(%d) %d = 197281\n\n", perft(4, board, currentPlayerColor) == 197281, perft(4, board, currentPlayerColor));
    }
    if (BOARD2) {
        printf("(%d) %d = 48\n", perft(1, board2, currentPlayerColor) == 48, perft(1, board2, currentPlayerColor));
        printf("(%d) %d = 2039\n", perft(2, board2, currentPlayerColor) == 2039, perft(2, board2, currentPlayerColor));
        printf("(%d) %d = 97862\n\n", perft(3, board2, currentPlayerColor) == 97862, perft(3, board2, currentPlayerColor));
    }
    if (BOARD3) {
        printf("(%d) %d = 14\n", perft(1, board3, currentPlayerColor) == 14, perft(1, board3, currentPlayerColor));
        printf("(%d) %d = 191\n", perft(2, board3, currentPlayerColor) == 191, perft(2, board3, currentPlayerColor));
        printf("(%d) %d = 2812\n\n", perft(3, board3, currentPlayerColor) == 2812, perft(3, board3, currentPlayerColor));
    }
    if (BOARD4) {
        printf("(%d) %d = 6\n", perft(1, board4, currentPlayerColor) == 6, perft(1, board4, currentPlayerColor));
        printf("(%d) %d = 264\n", perft(2, board4, currentPlayerColor) == 264, perft(2, board4, currentPlayerColor));
        printf("(%d) %d = 9467\n\n", perft(3, board4, currentPlayerColor) == 9467, perft(3, board4, currentPlayerColor));
    }
    if (BOARD5) {
        printf("(%d) %d = 44\n", perft(1, board5, currentPlayerColor) == 44, perft(1, board5, currentPlayerColor));
        printf("(%d) %d = 1486\n", perft(2, board5, currentPlayerColor) == 1486, perft(2, board5, currentPlayerColor));
        printf("(%d) %d = 62379\n\n", perft(3, board5, currentPlayerColor) == 62379, perft(3, board5, currentPlayerColor));
    }
    if (BOARD6) {
        printf("(%d) %d = 46\n", perft(1, board6, currentPlayerColor) == 46, perft(1, board6, currentPlayerColor));
        printf("(%d) %d = 2079\n", perft(2, board6, currentPlayerColor) == 2079, perft(2, board6, currentPlayerColor));
        printf("(%d) %d = 89890\n\n", perft(3, board6, currentPlayerColor) == 89890, perft(3, board6, currentPlayerColor));
    }
    if (TESTBOARD) {
        printf("(Test) %d\n", perft(1, testBoard, currentPlayerColor));
        printf("(Test) %d\n", perft(2, testBoard, currentPlayerColor));
        printf("(Test) %d\n\n", perft(3, testBoard, currentPlayerColor));
    }
}

