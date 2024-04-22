// Functions to handle board operations

#include "board.h"
#include "movegen.h"

void makeMove(Board board, int fromRow, int fromCol, int toRow, int toCol, bool isEnPassant) {
    board[toRow][toCol] = board[fromRow][fromCol];

    // Move the rook if castling
    if (board[toRow][toCol].type == 'K' && abs(toCol - fromCol) == 2) {
        int rookFromCol, rookToCol;
        if (toCol > fromCol) {
            // King side castling
            rookFromCol = 7;
            rookToCol = toCol - 1;
        } else {
            // Queen side castling
            rookFromCol = 0;
            rookToCol = toCol + 1;
        }
        board[toRow][rookToCol] = board[toRow][rookFromCol];
        board[toRow][rookFromCol].color = NONE;
        board[toRow][rookFromCol].type = EMPTY;
    }

    // Handles en passant rights
    if (board[toRow][toCol].type == 'P' && (fromRow - toRow == 2 || fromRow - toRow == -2))
        board[toRow][toCol].enPassantVulnerable = true;

    // Clear the source square
    board[fromRow][fromCol].color = NONE;
    board[fromRow][fromCol].type = EMPTY;

    // Handles en passant capture
    if (isEnPassant) {
        // Removes the captured pawn in en passant
        int direction = (board[toRow][toCol].color == WHITE) ? 1 : -1;
        board[toRow + direction][toCol].color = NONE;
        board[toRow + direction][toCol].type = EMPTY;
        board[toRow + direction][toCol].enPassantVulnerable = false;
    }
}

void undoMove(Board board, int fromRow, int fromCol, int toRow, int toCol) {
    board[fromRow][fromCol] = board[toRow][toCol];

    board[toRow][toCol].type = EMPTY;
    board[toRow][toCol].color = NONE;
}

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
