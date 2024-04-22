// Functions for generating valid moves

#include "movegen.h"
#include "board.h"

void clearMoves(struct Move moves[], int *moveCount) {
    memset(moves, 0, *moveCount + 1);
    *moveCount = 0;
}

void allValidMoves(Board board, struct Move moves[], struct Move enemyMoves[], int *moveCount, Color color) {
    validPawnMoves(board, moves, enemyMoves, moveCount, color);
    validKnightMoves(board, moves, moveCount, color);
    validBishopMoves(board, moves, moveCount, color);
    validRookMoves(board, moves, moveCount, color);
    validQueenMoves(board, moves, moveCount, color);
    validKingMoves(board, moves, moveCount, color);
}

// Checks if cordinates are within the bounds of the board
bool isInBounds(int y, int x) { return (y >= 0 && y < BOARD_SIZE && x >= 0 && x < BOARD_SIZE); }

bool isEnemy(Board board, int y, int x, Color color) { return (board[y][x].color == ((color == WHITE) ? BLACK : WHITE)); }

// Checks for all valid pawn moves on the board
void validPawnMoves(Board board, struct Move moves[], struct Move enemyMoves[], int *moveCount, Color color) {
    // Handles pawn direction based on color
    int direction = (color == WHITE) ? -1 : 1;

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == PAWN && board[row][col].color == color && isInBounds(row, col)) {
                // Handles pawn moving forward once and/or twice
                if (board[row + direction][col].color == NONE) {
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col};
                    if (((color == BLACK && row == 1) || (color == WHITE && row == 6)) && board[row + (2 * direction)][col].color == NONE) {
                        moves[(*moveCount)++] = (struct Move){row, col, row + (2 * direction), col};
                    }
                }

                // Handles pawn taking diagonally
                if (isEnemy(board, row + direction, col + 1, color))
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col + 1};
                if (isEnemy(board, row + direction, col - 1, color))
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col - 1};

                // Handles En Passant
                if (isEnemy(board, row, col - 1, color))
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col - 1, true};
                if (isEnemy(board, row, col + 1, color))
                    moves[(*moveCount)++] = (struct Move){row, col, row + direction, col + 1, true};
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
    int dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
    int dy[] = {1, -1, -1, 1, 0, 0, 1, -1};

    bool canMove = false;

    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == KING && board[row][col].color == color) {
                for (int i = 0; i < 8; i++) {
                    if (board[row + dy[i]][col + dx[i]].color == NONE && isInBounds(row + dy[i], col + dx[i])) {
                        moves[(*moveCount)++] = (struct Move){row, col, row + dy[i], col + dx[i]};
                        canMove = true;
                    } else if (isEnemy(board, row + dy[i], col + dx[i], color) && isInBounds(row + dy[i], col + dx[i])) {
                        moves[(*moveCount)++] = (struct Move){row, col, row + dy[i], col + dx[i]};
                        canMove = true;
                        break;
                    } else if (board[row + dy[i]][col + dx[i]].color == color)
                        break;
                }
            }

    // Castling Rights
    switch (color) {
    case (WHITE):
        if (board[7][4].type == KING && board[7][4].castleRights == true) {
            if (board[7][0].type == ROOK && board[7][0].castleRights == true) {
                moves[(*moveCount)++] = (struct Move){7, 4, 7, 2};
            }
            if (board[7][7].type == ROOK && board[7][7].castleRights == true) {
                moves[(*moveCount)++] = (struct Move){7, 4, 7, 6};
            }
        }
        break;
    case (BLACK):
        if (board[7][4].type == KING && board[7][4].castleRights == true) {
            if (board[0][0].type == ROOK && board[0][0].castleRights == true) {
                moves[(*moveCount)++] = (struct Move){0, 4, 0, 2};
            }
            if (board[0][7].type == ROOK && board[0][7].castleRights == true) {
                moves[(*moveCount)++] = (struct Move){0, 4, 0, 6};
            }
        }

        break;
    }
    return canMove;
}

// Checks and performs pawn promotion for user
void isThereUserPromotion(Board board, Color color) {
    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == PAWN && ((row == 0 && color == WHITE) || (row == 7 && color == BLACK))) {
                printf("Pick between (1)Queen, (2)Rook, (3)Bishop, (4)Knight for your pawns promotion. \n");
                int promotion = 0;
                do {
                    scanf("%d", &promotion);
                } while (!(promotion > 0 && promotion < 5));

                while (1) {
                    switch (promotion) {
                    case (1):
                        board[row][col].type = QUEEN;
                        return;
                    case (2):
                        board[row][col].type = ROOK;
                        return;
                    case (3):
                        board[row][col].type = BISHOP;
                        return;
                    case (4):
                        board[row][col].type = KNIGHT;
                        return;
                    default:
                        printf("Invalid input, please pick again");
                    }
                }
            }
}

// Checks and performs pawn promotion for bot
void isThereBotPromotion(Board board, Color color) {
    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++)
            if (board[row][col].type == PAWN && ((row == 0 && color == WHITE) || (row == 7 && color == BLACK))) {
                int promotion = rand() % 4 + 1;
                switch (promotion) {
                case (1):
                    board[row][col].type = QUEEN;
                    return;
                case (2):
                    board[row][col].type = ROOK;
                    return;
                case (3):
                    board[row][col].type = BISHOP;
                    return;
                case (4):
                    board[row][col].type = KNIGHT;
                    return;
                }
            }
}

// Checks whether a square is under attack or not
bool isUnderAttack(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color defenderColor, int squareRow, int squareCol) {
    for (int i = 0; i < *attackerMoveCount; i++) {
        if (attackerMoves[i].toRow == squareRow && attackerMoves[i].toCol == squareCol && board[squareRow][squareCol].color == defenderColor) {
            return true;
        }
    }
    return false;
}

// Checks whether the king is checked or just chilling :)
bool isChecked(Board board, struct Move attackerMoves[], int *attackerMoveCount, Color defenderColor) {
    for (int row = 0; row < BOARD_SIZE; row++)
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col].type == KING && board[row][col].color == defenderColor &&
                isUnderAttack(board, attackerMoves, attackerMoveCount, defenderColor, row, col))
                return true;
        }
    return false;
}

// Checks whether the king is checkmated or not, should only get called if isChecked is true
bool isCheckmated(Board board, struct Move attackerMoves[], struct Move defenderMoves[], int *attackerMoveCount, int *defenderMoveCount, Color defenderColor) {
    bool isMated = true;
    clearMoves(defenderMoves, defenderMoveCount);

    for (int i = 0; i < *defenderMoveCount; i++) {
        makeMove(board, defenderMoves[i].fromRow, defenderMoves[i].fromCol, defenderMoves[i].toRow, defenderMoves[i].toCol, defenderMoves[i].isEnPassant);
        if (!isChecked(board, attackerMoves, attackerMoveCount, defenderColor)) {
            // If move to get out of mate is found, add it to possible moves list

            defenderMoves[(*defenderMoveCount)++] =
                (struct Move){defenderMoves[i].fromRow, defenderMoves[i].fromCol, defenderMoves[i].toRow, defenderMoves[i].toCol};

            isMated = false;
        }
        undoMove(board, defenderMoves[i].fromRow, defenderMoves[i].fromCol, defenderMoves[i].toRow, defenderMoves[i].toCol);
    }

    return isMated;
}

