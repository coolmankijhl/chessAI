// Functions to handle board operations

#include "board.h"

// Prints board white side
void printBoard(Board board) {
    for (int i = 0; i < 8; i++) {
        printf("%d|", 8 - i);
        for (int j = 0; j < 8; j++) {
            if (board[i][j].color == WHITE)
                printf("\e[0;37m\e[4;37m");
            else if (board[i][j].color == BLACK)
                printf("\e[0;30m\e[4;30m");
            printf("%c\e[0m|", board[i][j].type);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

