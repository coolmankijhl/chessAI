#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define PAWN_VALUE 1
#define KNIGHT_VALUE 3
#define BISHOP_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9
#define KING_VALUE 999999

int evaluateBoard(Board board);
struct Move findBestMove(Board board, int depth, Color currentPlayerColor);
int minimax(Board board, int depth, int alpha, int beta, bool maximizing);
