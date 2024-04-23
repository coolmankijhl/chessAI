// Functions to handle board operations

#include "board.h"
#include "movegen.h"

struct historyNode {
    PieceType typeTaken;
    Color colorTaken;
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
};

struct historyNode history[1000];
int historyIndex = 0;

void makeMove(Board board, int fromRow, int fromCol, int toRow, int toCol) {
    // Store the details of the move in the history
    if (historyIndex < 1000) {
        history[historyIndex].typeTaken = board[toRow][toCol].type;
        history[historyIndex].colorTaken = board[toRow][toCol].color;
        history[historyIndex].fromRow = fromRow;
        history[historyIndex].fromCol = fromCol;
        history[historyIndex].toRow = toRow;
        history[historyIndex].toCol = toCol;
        historyIndex++;
    } else {
        printf("Move history is full.\n");
        return;
    }

    // Move the piece from the source square to the destination square
    board[toRow][toCol] = board[fromRow][fromCol];

    // Clear the source square
    board[fromRow][fromCol].type = EMPTY;
    board[fromRow][fromCol].color = NONE;
}

void undoMove(Board board) {
    if (historyIndex > 0) {
        // Decrement history index to access the last move
        historyIndex--;

        // Retrieve the details of the last move
        int fromRow = history[historyIndex].fromRow;
        int fromCol = history[historyIndex].fromCol;
        int toRow = history[historyIndex].toRow;
        int toCol = history[historyIndex].toCol;

        // Restore the moved piece to its original position
        board[fromRow][fromCol] = board[toRow][toCol];

        // Restore the piece that was taken, if any
        board[toRow][toCol].type = history[historyIndex].typeTaken;
        board[toRow][toCol].color = history[historyIndex].colorTaken;
    } else {
        printf("No moves to undo.\n");
    }
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
