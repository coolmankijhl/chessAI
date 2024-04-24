#include "engine.h"
#include "board.h"
#include "movegen.h"

#define MAX_DEPTH 10 // Adjust the maximum depth according to your computational resources

// Evaluation function to evaluate the board state
int evaluateBoard(Board board) {
    int score = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Piece piece = board[row][col];
            switch (piece.type) {
            case PAWN:
                score += (piece.color == WHITE) ? PAWN_VALUE : -PAWN_VALUE;
                break;
            case KNIGHT:
                score += (piece.color == WHITE) ? KNIGHT_VALUE : -KNIGHT_VALUE;
                break;
            case BISHOP:
                score += (piece.color == WHITE) ? BISHOP_VALUE : -BISHOP_VALUE;
                break;
            case ROOK:
                score += (piece.color == WHITE) ? ROOK_VALUE : -ROOK_VALUE;
                break;
            case QUEEN:
                score += (piece.color == WHITE) ? QUEEN_VALUE : -QUEEN_VALUE;
                break;
            case KING:
                score += (piece.color == WHITE) ? KING_VALUE : -KING_VALUE;
                break;
            }
        }
    }
    return score;
}

// Minimax function
int minimax(Board board, int depth, bool maximizingPlayer) {
    if (depth == 0) {
        // Evaluate the current board state at leaf nodes
        return evaluateBoard(board);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        // Generate all possible moves for the current player
        struct Move moves[MAX_MOVES];
        int moveCount = 0;
        allValidMoves(board, moves, &moveCount, WHITE, BLACK);
        for (int i = 0; i < moveCount; i++) {
            // Make the move
            makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, true);
            // Recursively call minimax with reduced depth and switching player
            int eval = minimax(board, depth - 1, false);
            // Undo the move
            undoMove(board, BLACK);
            maxEval = max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        // Generate all possible moves for the opponent
        struct Move moves[MAX_MOVES];
        int moveCount = 0;
        allValidMoves(board, moves, &moveCount, BLACK, WHITE);
        for (int i = 0; i < moveCount; i++) {
            // Make the move
            makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, false);
            // Recursively call minimax with reduced depth and switching player
            int eval = minimax(board, depth - 1, true);
            // Undo the move
            undoMove(board, WHITE);
            minEval = min(minEval, eval);
        }
        return minEval;
    }
}

// Function to find the best move using minimax algorithm
struct Move findBestMove(Board board, int depth) {
    int bestMoveIndex = -1;
    int bestEval = INT_MIN;
    // Generate all possible moves for the current player
    struct Move moves[MAX_MOVES];
    int moveCount = 0;
    allValidMoves(board, moves, &moveCount, WHITE, BLACK);
    for (int i = 0; i < moveCount; i++) {
        // Make the move
        makeMove(board, moves[i].fromRow, moves[i].fromCol, moves[i].toRow, moves[i].toCol, true);
        // Evaluate the move using minimax with reduced depth
        int eval = minimax(board, depth - 1, false);
        // Undo the move
        undoMove(board, BLACK);
        if (eval > bestEval) {
            bestEval = eval;
            bestMoveIndex = i;
        }
    }
    // Return the best move found
    return moves[bestMoveIndex];
}

