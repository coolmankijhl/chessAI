// Functions to handle board operations

#include "board.h"
#include "movegen.h"

void makeMove(Board board, int fromRow, int fromCol, int toRow, int toCol) {
    // Save the piece from the source square
    Piece temp = board[fromRow][fromCol];

    // Move the piece from the source square to the destination square
    board[fromRow][fromCol] = board[toRow][toCol];
    board[toRow][toCol] = temp;
}

void undoMove(Board board, int fromRow, int fromCol, int toRow, int toCol) {
    // Swap the pieces back to their original positions
    Piece temp = board[fromRow][fromCol];
    board[fromRow][fromCol] = board[toRow][toCol];
    board[toRow][toCol] = temp;
}

// Prints board white side
void printBoard(Board board) {
    for (int i = 0; i < 8; i++) {
        printf("%d|", 8 - i);
        for (int j = 0; j < 8; j++) {
            if (board[i][j].color == WHITE)
                printf("\e[0;37m\e[4;37m");
            else if (board[i][j].color == BLACK)
                printf("\e[0;32m\e[4;32m");
            printf("%c\e[0m|", board[i][j].type);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}
