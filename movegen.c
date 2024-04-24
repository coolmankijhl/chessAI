// Functions for generating valid moves

#include "movegen.h"
#include "board.h"

#define DONTPRINT 0

void clearMoves(struct Move moves[], int *moveCount) {
    memset(moves, -1, *moveCount + 1);
    *moveCount = 0;
}

void allValidMoves(Board board, struct Move moves[], int *moveCount, struct Move enemyMoves[], int *enemyMoveCount, Color color, Color enemyColor) {
    clearMoves(moves, moveCount);
    clearMoves(enemyMoves, enemyMoveCount);

    validPawnMoves(board, moves, moveCount, color);
    validKnightMoves(board, moves, moveCount, color);
    validBishopMoves(board, moves, moveCount, color);
    validRookMoves(board, moves, moveCount, color);
    validQueenMoves(board, moves, moveCount, color);
    validKingMoves(board, moves, moveCount, color);

    validPawnMoves(board, enemyMoves, enemyMoveCount, enemyColor);
    validKnightMoves(board, enemyMoves, enemyMoveCount, enemyColor);
    validBishopMoves(board, enemyMoves, enemyMoveCount, enemyColor);
    validRookMoves(board, enemyMoves, enemyMoveCount, enemyColor);
    validQueenMoves(board, enemyMoves, enemyMoveCount, enemyColor);
    validKingMoves(board, enemyMoves, enemyMoveCount, enemyColor);

    if (isCheck(board, enemyMoves, enemyMoveCount, color)) {
        if (!DONTPRINT) {
            printf("Check.\n");
        }
    }
}

// Checks if cordinates are within the bounds of the board
bool isInBounds(int y, int x) { return (y >= 0 && y < BOARD_SIZE && x >= 0 && x < BOARD_SIZE); }

bool isEnemy(Board board, int y, int x, Color color) { return (board[y][x].color == ((color == WHITE) ? BLACK : WHITE)); }

void validPawnMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    if (moves == NULL || moveCount == NULL) {
        // Handle invalid input
        return;
    }

    // Handles pawn direction based on color
    int direction = (color == WHITE) ? -1 : 1;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (isInBounds(row, col) && board[row][col].type == PAWN && board[row][col].color == color) {
                // Handles pawn moving forward once and/or twice
                if (isInBounds(row + direction, col) && board[row + direction][col].color == NONE) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col};
                    if (((color == BLACK && row == 1) || (color == WHITE && row == 6)) && isInBounds(row + (2 * direction), col) &&
                        board[row + (2 * direction)][col].color == NONE) {
                        moves[(*moveCount)++] = (struct Move){row, col, row + (2 * direction), col};

                        // Makes En Passant Available to adajcent enemy pawns
                        if (board[row + (2 * direction)][col - 1].type == PAWN && isEnemy(board, (row + (2 * direction)), col - 1, color)) {
                            board[row + (2 * direction)][col - 1].enPassantAvailable = true;
                        }
                        if (board[row + (2 * direction)][col + 1].type == PAWN && isEnemy(board, (row + (2 * direction)), col + 1, color)) {
                            board[row + (2 * direction)][col + 1].enPassantAvailable = true;
                        }
                    }
                }

                // Handles pawn taking diagonally
                if (isEnemy(board, row + direction, col + 1, color) && isInBounds(row + direction, col + 1)) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col + 1};
                }
                if (isEnemy(board, row + direction, col - 1, color) && isInBounds(row + direction, col - 1)) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col - 1};
                }

                // Handles pawns taking with En Passant
                if (board[row][col].enPassantAvailable == true && isEnemy(board, row, col - 1, color) && board[row][col - 1].enPassantVulnerable == true &&
                    isInBounds(row + direction, col - 1)) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col - 1};
                }
                if (board[row][col].enPassantAvailable == true && isEnemy(board, row, col + 1, color) && board[row][col + 1].enPassantVulnerable == true &&
                    isInBounds(row + direction, col + 1)) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col + 1};
                }
            }
        }
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
                    // Checks if knight move is in bounds and possible, adds it if so
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

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == BISHOP && board[row][col].color == color) {
                for (int i = 0; i < 4; i++) {
                    int toRow = row + dy[i];
                    int toCol = col + dx[i];
                    while (isInBounds(toRow, toCol)) {
                        if (board[toRow][toCol].color == NONE) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                        } else if (isEnemy(board, toRow, toCol, color)) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                            break;
                        } else if (board[toRow][toCol].color == color) {
                            break;
                        }
                        toRow += dy[i];
                        toCol += dx[i];
                    }
                }
            }
        }
    }
}

// Checks for all valid queen moves on the board
void validQueenMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    int dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
    int dy[] = {1, -1, -1, 1, 0, 0, 1, -1};

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == QUEEN && board[row][col].color == color) {
                for (int i = 0; i < 8; i++) {
                    int toRow = row + dy[i];
                    int toCol = col + dx[i];
                    while (isInBounds(toRow, toCol)) {
                        if (board[toRow][toCol].color == NONE) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                        } else if (isEnemy(board, toRow, toCol, color)) {
                            moves[(*moveCount)++] = (struct Move){row, col, toRow, toCol};
                            break;
                        } else if (board[toRow][toCol].color == color) {
                            break;
                        }
                        toRow += dy[i];
                        toCol += dx[i];
                    }
                }
            }
        }
    }
}

// Checks for all valid king moves on the board
bool validKingMoves(Board board, struct Move moves[], int *moveCount, Color color) {
    int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[] = {0, 0, 1, -1, 1, 1, -1, -1};

    bool canMove = false;

    // Iterate over the board
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            // Check for king of the given color
            if (board[row][col].type == KING && board[row][col].color == color) {
                // Iterate over all possible king moves
                for (int i = 0; i < 8; i++) {
                    int newRow = row + dy[i];
                    int newCol = col + dx[i];
                    // Check if the new position is within bounds and empty or contains an enemy piece
                    if (isInBounds(newRow, newCol) && (board[newRow][newCol].color == NONE || isEnemy(board, newRow, newCol, color))) {
                        moves[(*moveCount)++] = (struct Move){row, col, newRow, newCol};
                        canMove = true;
                    }
                }
            }
        }
    }

    // Castling Rights
    switch (color) {
    case WHITE:
        // Check if king and rooks have the right to castle
        if (board[7][4].type == KING && board[7][4].castleRights && !isUnderAttack(board, moves, moveCount, color, 7, 4)) {
            // Queen side castling
            if (board[7][0].type == ROOK && board[7][0].castleRights && board[7][1].type == EMPTY && board[7][2].type == EMPTY && board[7][3].type == EMPTY &&
                !isUnderAttack(board, moves, moveCount, color, 7, 4) && !isUnderAttack(board, moves, moveCount, color, 7, 3)) {
                moves[(*moveCount)++] = (struct Move){7, 4, 7, 2};
                canMove = true;
            }
            // King side castling
            if (board[7][7].type == ROOK && board[7][7].castleRights && board[7][5].type == EMPTY && board[7][6].type == EMPTY &&
                !isUnderAttack(board, moves, moveCount, color, 7, 4) && !isUnderAttack(board, moves, moveCount, color, 7, 5)) {
                moves[(*moveCount)++] = (struct Move){7, 4, 7, 6};
                canMove = true;
            }
        }
        break;

    case BLACK:
        if (board[0][4].type == KING && board[0][4].castleRights && !isUnderAttack(board, moves, moveCount, color, 0, 4)) {
            // Queen side castling
            if (board[7][0].type == ROOK && board[0][0].castleRights && board[0][1].type == EMPTY && board[0][2].type == EMPTY && board[0][3].type == EMPTY &&
                !isUnderAttack(board, moves, moveCount, color, 0, 4) && !isUnderAttack(board, moves, moveCount, color, 0, 3)) {
                moves[(*moveCount)++] = (struct Move){0, 4, 0, 2};
                canMove = true;
            }
            // King side castling
            if (board[0][7].type == ROOK && board[0][7].castleRights && board[0][5].type == EMPTY && board[0][6].type == EMPTY &&
                !isUnderAttack(board, moves, moveCount, color, 0, 4) && !isUnderAttack(board, moves, moveCount, color, 0, 5)) {
                moves[(*moveCount)++] = (struct Move){0, 4, 0, 6};
                canMove = true;
            }
        }

        break;
    }

    return canMove;
}

bool isUnderAttack(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color defenderColor, int squareRow, int squareCol) {
    for (int i = 0; i < *attackerMoveCount; i++) {
        if (attackerMoves[i].toRow == squareRow && attackerMoves[i].toCol == squareCol && board[squareRow][squareCol].color == defenderColor) {
            return true;
        }
    }

    return false;
}

bool isCheck(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color playerColor) {
    // Find the position of the king of the player
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == KING && board[row][col].color == playerColor) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1 && kingCol != -1)
            break;
    }

    return isUnderAttack(board, attackerMoves, attackerMoveCount, playerColor, kingRow, kingCol);
}

bool isCheckmate(Board board) {
    bool whiteKingFound = false;
    bool blackKingFound = false;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == KING && board[row][col].color == WHITE) {
                whiteKingFound = true;
                break;
            }
        }

        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == KING && board[row][col].color == BLACK) {
                blackKingFound = true;
                break;
            }
        }
    }

    if (!whiteKingFound) {
        if (!DONTPRINT) {
            printf("BLACK wins\n!");
        }
        return true;
    } else if (!blackKingFound) {
        if (!DONTPRINT) {
            printf("WHITE wins\n!");
        }
        return true;
    }

    return false;
}
