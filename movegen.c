// Functions for generating valid moves

#include "movegen.h"

void clearMoves(struct Move moves[], int *moveCount) {
    memset(moves, 0, *moveCount + 1);
    *moveCount = 0;
}

void allValidMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    validPawnMoves(board, moves, moveCount, color);
    validKnightMoves(board, moves, moveCount, color);
    validBishopMoves(board, moves, moveCount, color);
    validRookMoves(board, moves, moveCount, color);
    validQueenMoves(board, moves, moveCount, color);
    validKingMoves(board, moves, moveCount, color);

    // for(int i = 0; i < moveCount; i++)
    //{
    //         printf("(%d) %d %d -> %d %d\n", i+1, moves[i].fromRow,
    //         moves[i].fromCol, moves[i].toRow, moves[i].toCol);
    // }
}

// Checks if cordinates are within the bounds of the board
bool isInBounds(int y, int x) { return (y >= 0 && y < BOARD_SIZE && x >= 0 && x < BOARD_SIZE); }

bool isEnemy(Board board, int y, int x, Color color) { return (board[y][x].color == ((color == WHITE) ? BLACK : WHITE)); }

// Checks for all valid pawn moves on the board
void validPawnMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    // Handles pawn direction based on color
    int direction = (color == WHITE) ? -1 : 1;

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == PAWN) {
                // Handles pawn moving forward once and/or twice
                if (((color == BLACK && row == 1) || (color == WHITE && row == 6)) && board[row + direction][col].color == NONE) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col};
                    if (board[row + (2 * direction)][col].color == NONE)
                        moves[(*moveCount)++] = (struct Move){row, col, row + (2 * direction), col};
                }

                // Handles pawn taking diagonally
                if (isEnemy(board, row + direction, col + 1, color) && board[row][col].color == color)
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col + 1};
                if (isEnemy(board, row + direction, col - 1, color) && board[row][col].color == color)
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col - 1};
            }
}

// Checks for all valid knight moves on the board
void validKnightMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    // Possible knight moves
    int dx[] = {-2, -2, 2, 2, -1, 1, -1, 1};
    int dy[] = {-1, 1, -1, 1, -2, -2, 2, 2};

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == KNIGHT && board[row][col].color == color)
                for (int i = 0; i < 8; i++) {
                    // Checks if knight move is in bounds and possible, adds it
                    // if so
                    if (isInBounds(row + dy[i], col + dx[i]) && board[row + dy[i]][col + dx[i]].color != color)
                        moves[(*moveCount)++] = (struct Move){row, col, row + dy[i], col + dx[i]};
                }
}

// Checks for all valid rook moves on the board
void validRookMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    // Rook directional indices
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == ROOK && board[row][col].color == color) {
                for (int i = 0; i < 4; i++) {
                    int toRow = row + dy[i];
                    int toCol = col + dx[i];
                    while (isInBounds(toRow, toCol)) {
                        if (board[toRow][toCol].color == NONE && isInBounds(toRow, toCol))
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                        else if (isEnemy(board, toRow, toCol, color) && isInBounds(toRow, toCol)) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                            break;
                        } else if (board[toRow][toCol].color == color)
                            break;

                        toRow += dy[i];
                        toCol += dx[i];
                    }
                }
            }
}

// Checks for all valid bishop moves on the board
void validBishopMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    int dx[] = {1, -1, 1, -1};
    int dy[] = {1, -1, -1, 1};

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == BISHOP && board[row][col].color == color) {
                for (int i = 0; i < 4; i++) {
                    int toRow = row + dy[i];
                    int toCol = col + dx[i];
                    for (int j = 0; j < 8; j++) {
                        if (board[toRow][toCol].color == NONE && isInBounds(toRow, toCol))
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                        else if (isEnemy(board, toRow, toCol, color) && isInBounds(toRow, toCol)) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                            break;
                        } else if (board[toRow][toCol].color == color)
                            break;

                        toRow += dy[i];
                        toCol += dx[i];
                    }
                }
            }
}

// Checks for all valid queen moves on the board
void validQueenMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    int dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
    int dy[] = {1, -1, -1, 1, 0, 0, 1, -1};

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == QUEEN && board[row][col].color == color) {
                for (int i = 0; i < 8; i++) {
                    int toRow = row + dy[i];
                    int toCol = col + dx[i];
                    for (int j = 0; j < 8; j++) {
                        if (board[toRow][toCol].color == NONE && isInBounds(toRow, toCol))
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                        else if (isEnemy(board, toRow, toCol, color) && isInBounds(toRow, toCol)) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                            break;
                        } else if (board[toRow][toCol].color == color)
                            break;

                        toRow += dy[i];
                        toCol += dx[i];
                    }
                }
            }
}

// Checks for all valid king moves on the board
void validKingMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    int dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
    int dy[] = {1, -1, -1, 1, 0, 0, 1, -1};

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == KING && board[row][col].color == color) {
                for (int i = 0; i < 8; i++) {
                    if (board[row + dy[i]][col + dx[i]].color == NONE && isInBounds(row + dy[i], col + dx[i]))
                        moves[(*moveCount)++] = (struct Move){row, col, row + dy[i], col + dx[i]};
                    else if (isEnemy(board, row + dy[i], col + dx[i], color) && isInBounds(row + dy[i], col + dx[i])) {
                        moves[(*moveCount)++] = (struct Move){row, col, row + dy[i], col + dx[i]};
                        break;
                    } else if (board[row + dy[i]][col + dx[i]].color == color)
                        break;
                }
            }
}
