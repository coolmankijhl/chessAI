// Functions to handle board operations

#include "board.h"
#include "movegen.h"

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
    } else {
        printf("Move history is full.\n");
        return;
    }

    // Move the piece from the source square to the destination square
    board[toRow][toCol] = board[fromRow][fromCol];

    // Clear the source square
    board[fromRow][fromCol].type = EMPTY;
    board[fromRow][fromCol].color = NONE;

    // Handles Castling
    if (abs(fromCol - toCol) == 2 && board[toRow][toCol].type == KING) {
        history[historyIndex].castleRow = toRow;
        history[historyIndex].castled = true;
        board[toRow][toCol].castleRights = false;
        // Queen side
        if (toCol > fromCol) {
            history[historyIndex].castleCol = 7;
            board[toRow][toCol - 1] = board[toRow][7];
            board[toRow][7].type = EMPTY;
            board[toRow][7].color = NONE;
            // King side
        } else {
            history[historyIndex].castleCol = 0;
            board[toRow][toCol + 1] = board[toRow][0];
            board[toRow][0].type = EMPTY;
            board[toRow][0].color = NONE;
        }
    }

    // If rook or king moves remove castle rights
    if (board[toRow][toCol].type == ROOK || board[toRow][toCol].type == KING) {
        board[toRow][toCol].castleRights = false;
    }

    // Iterate over the entire board to remove enPassantAvailable for all pawns
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == PAWN) {
                board[row][col].enPassantAvailable = false;
                board[row][col].enPassantVulnerable = false;
            }
        }
    }

    // Check if a pawn makes a double move and set enPassantVulnerable
    if (board[toRow][toCol].type == PAWN && abs(fromRow - toRow) == 2) {
        // Set enPassantVulnerable for the pawn
        board[toRow][toCol].enPassantVulnerable = true;
    }

    // Remove the captured pawn in en passant
    if (board[toRow][toCol].type == PAWN && abs(fromCol - toCol) == 1 && board[toRow][toCol].enPassantAvailable == true) {
        // Determine the row of the captured pawn
        int capturedRow = (board[toRow][toCol].color == WHITE) ? toRow + 1 : toRow - 1;
        // Clear the square of the captured pawn
        board[capturedRow][toCol].type = EMPTY;
        board[capturedRow][toCol].color = NONE;
    }

    historyIndex++;
}

void undoMove(Board board, Color playerColor) {
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

        // Check if castling was performed in the move being undone
        if (history[historyIndex].castled) {
            board[history[historyIndex].castleRow][history[historyIndex].castleCol].type = 'R';
            board[history[historyIndex].castleRow][history[historyIndex].castleCol].color = playerColor;
            if (toCol - fromCol == -2) {
                // Queen side
                board[history[historyIndex].castleRow][history[historyIndex].castleCol + 3].type = EMPTY;
                board[history[historyIndex].castleRow][history[historyIndex].castleCol + 3].color = NONE;
            } else if (toCol - fromCol == 2) {
                // King side
                board[history[historyIndex].castleRow][history[historyIndex].castleCol - 2].type = EMPTY;
                board[history[historyIndex].castleRow][history[historyIndex].castleCol - 2].color = NONE;
            }
        }
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
