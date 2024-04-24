#include <limits.h>
#include <stdio.h>

#include "board.h"
#include "engine.h"
#include "movegen.h"

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }

int evaluateBoard(Board board) {
    int score = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Piece piece = board[row][col];
            switch (piece.type) {
            case PAWN:
                score += (board[row][col].color == WHITE) ? KING_VALUE : -KING_VALUE;
                break;
            case KNIGHT:
                score += (board[row][col].color == WHITE) ? KING_VALUE : -KING_VALUE;
                break;
            case BISHOP:
                score += (board[row][col].color == WHITE) ? KING_VALUE : -KING_VALUE;
                break;
            case ROOK:
                score += (board[row][col].color == WHITE) ? KING_VALUE : -KING_VALUE;
                break;
            case QUEEN:
                score += (board[row][col].color == WHITE) ? KING_VALUE : -KING_VALUE;
                break;
            case KING:
                score += (board[row][col].color == WHITE) ? KING_VALUE : -KING_VALUE;
            }
        }
    }
    return score;
}

int minimax(Board board, int depth, int alpha, int beta, bool maximizing) {
    // Check if reached the maximum depth or if it's a terminal state (e.g., checkmate)
    if (depth == 0 /*or checkmate*/) {
        // Return the evaluation of the current board state
        return evaluateBoard(board);
    }

    if (maximizing) {
        int maxScore = INT_MIN; // Initialize the maximum score

        // Find all possible moves for the maximizing player
        struct Move moves[500];
        int moveCount = 0;
        struct Move enemyMoves[500];
        int enemyMoveCount = 0;
        allValidMoves(board, moves, &moveCount, enemyMoves, &enemyMoveCount, WHITE, BLACK);

        // Loop through all possible moves
        for (int i = 0; i < moveCount; i++) {
            makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, true);
            int score = minimax(board, depth - 1, alpha, beta, false); // Recursively call minimax for the next depth
            maxScore = max(maxScore, score);
            alpha = max(alpha, maxScore);
            undoMove(board, WHITE);

            if (beta <= alpha)
                break; // Beta cut-off
        }
        return maxScore;
    } else {
        int minScore = INT_MAX;
        struct Move moves[500];
        int moveCount = 0;
        struct Move enemyMoves[500];
        int enemyMoveCount = 0;
        allValidMoves(board, moves, &moveCount, enemyMoves, &enemyMoveCount, BLACK, WHITE);

        for (int i = 0; i < moveCount; i++) {
            makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, true);
            int score = minimax(board, depth - 1, alpha, beta, true);
            minScore = min(minScore, score);
            beta = min(beta, minScore);
            undoMove(board, BLACK);

            if (beta <= alpha)
                break; // Alpha cut-off
        }
        return minScore;
    }
}

struct Move findBestMove(Board board, int depth, Color currentPlayerColor) {
    int bestScore = INT_MIN;
    struct Move bestMove;
    struct Move moves[500];
    int moveCount = 0;
    struct Move enemyMoves[500];
    int enemyMoveCount = 0;
    allValidMoves(board, moves, &moveCount, enemyMoves, &enemyMoveCount, currentPlayerColor, ((currentPlayerColor == WHITE) ? BLACK : WHITE));

    // Alpha and beta initialization
    int alpha = INT_MIN;
    int beta = INT_MAX;

    // Loop through all possible moves
    for (int i = 0; i < moveCount; i++) {
        makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, true);
        int score = minimax(board, depth - 1, alpha, beta, false);
        undoMove(board, WHITE);

        // If the score is better than the current best score, update the best move
        if (score > bestScore) {
            bestScore = score;
            bestMove = moves[i];
        }
        alpha = max(alpha, bestScore);
    }
    return bestMove;
}

