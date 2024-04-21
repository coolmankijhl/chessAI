#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BOARD_SIZE 8

	
struct Piece
{
	int color;
	char type;
};

struct MoveSet
{
	int ROW;
	int COL;
	int toROW;
	int toCOL;
};

enum pieceData
{
	EMPTY,	//0
	WHITE,	//1
	BLACK,	//2
};

bool isInBounds(int y, int x);
void printBoard();
void parser();
void validPawnMoves(struct MoveSet moves[], int *moveCount, int color);
void validKnightMoves(struct MoveSet moves[], int *moveCount, int color);
void validRookMoves(struct MoveSet moves[], int *moveCount, int color);
void validBishopMoves(struct MoveSet moves[], int *moveCount, int color);
void validQueenMoves(struct MoveSet moves[], int *moveCount, int color);
void validKingMoves(struct MoveSet moves[], int *moveCount, int color);

struct Piece board[BOARD_SIZE][BOARD_SIZE] = {
	{{2,'R'},{2,'N'},{2,'B'},{2,'Q'},{2,'K'},{2,'B'},{2,'N'},{2,'R'}},
	{{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'}},
	{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
	{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
	{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
	{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
	{{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'}},
	{{1,'R'},{1,'N'},{1,'B'},{1,'Q'},{1,'K'},{1,'B'},{1,'N'},{1,'R'}}
};

// Prints board white side
void printBoard()
{
	for(int i = 0; i < 8; i++)
	{
		printf("%d|", 8-i);
		for(int j = 0; j < 8; j++)
		{
			if(board[i][j].color == WHITE)
				printf("\e[0;37m\e[4;37m");
			else if(board[i][j].color == BLACK)
				printf("\e[0;30m\e[4;30m");
			printf("%c\e[0m|", board[i][j].type);
		}
		printf("\n");
	}
	printf("  a b c d e f g h\n");
}

// Takes in input and converts values to 0-7
void parser()
{
	char userInput[6] = "";
	char userArgs[2][3] = {"", ""};

	fgets(userInput, sizeof(userInput), stdin);

	sscanf(userInput, "%s %s ", userArgs[0], userArgs[1]);

	int y1 = 56-(int)userArgs[0][1];
	int x1 = (int)toupper(userArgs[0][0])-65;

	int y2 = 56-(int)userArgs[1][1];
	int x2 = (int)toupper(userArgs[1][0])-65;
}

// Checks if cordinates are within the bounds of the board
bool isInBounds(int y, int x)
{
	return (y >= 0 && y <= BOARD_SIZE-1 && x >= 0 && x <= BOARD_SIZE-1);
}

// Checks for all valid pawn moves on the board
void validPawnMoves(struct MoveSet moves[], int *moveCount, int color)
{
	// Handles pawn direction based on color
	int direction = (color == WHITE) ? -1 : 1;

	for(int ROW = 0; ROW < BOARD_SIZE; ROW++)
		for(int COL = 0; COL < BOARD_SIZE; COL++)
			if(board[ROW][COL].type == 'P')
			{
				// Handles pawn moving forward once and/or twice
				if(((color == BLACK && ROW == 1) || (color == WHITE && ROW == 6)) && board[ROW+direction][COL].color == EMPTY && board[ROW+(direction*2)][COL].color == EMPTY)
					moves[(*moveCount)++] = (struct MoveSet){ROW, COL, ROW+(2*direction), COL};
				if(board[ROW+direction][COL].color == EMPTY)
					moves[(*moveCount)++] = (struct MoveSet){ROW, COL, ROW+direction, COL};
			
				// Handles pawn taking diagonally	
				if(board[ROW+direction][COL+1].color == ((color == WHITE) ? BLACK : WHITE) && board[ROW][COL].color == color)
					moves[(*moveCount)++] = (struct MoveSet){ROW, COL+direction, ROW+1, COL};
				if(board[ROW+direction][COL-1].color == ((color == WHITE) ? BLACK : WHITE) && board[ROW][COL].color == color)
					moves[(*moveCount)++] = (struct MoveSet){ROW, COL+direction, ROW-1, COL};
			}
}

// Checks for all valid knight moves on the board
void validKnightMoves(struct MoveSet moves[], int *moveCount, int color)
{
	// Possible knight moves
	int dx[] = {-2, -2, 2, 2, -1, 1, -1, 1};
	int dy[] = {-1, 1, -1, 1, -2, -2, 2, 2};

	for(int ROW = 0; ROW < BOARD_SIZE; ROW++)
		for(int COL = 0; COL < BOARD_SIZE; COL++)
			if(board[ROW][COL].type == 'N' && board[ROW][COL].color == color)
				for(int i = 0; i < 8; i++)
				{
					// Checks if knight move is in bounds and possible, adds it if so
					if(isInBounds(ROW+dy[i], COL+dx[i]) && board[ROW+dy[i]][COL+dx[i]].color != color)
						moves[(*moveCount)++] = (struct MoveSet){ROW, COL, ROW+dy[i], COL+dx[i]};	
				}
}

// Checks for all valid rook moves on the board
void validRookMoves(struct MoveSet moves[], int *moveCount, int color)
{
	// Rook directional indices
	int dx[] = {1, -1, 0, 0};
	int dy[] = {0, 0, 1, -1};

	for(int ROW = 0; ROW < BOARD_SIZE; ROW++)
		for(int COL = 0; COL < BOARD_SIZE; COL++)
			if(board[ROW][COL].type == 'R' && board[ROW][COL].color == color)
			{
				for(int i = 0; i < 4; i++)
				{
					int toROW = ROW + dy[i];
					int toCOL = COL + dx[i];
					for(int j = 0; j < 8; j++)
					{
						if(board[toROW][toCOL].color == EMPTY && isInBounds(toROW, toCOL))
							moves[(*moveCount)++] = (struct MoveSet){ROW, COL, toROW, toCOL};	
						else if(board[toROW][toCOL].color == ((color == WHITE) ? BLACK : WHITE) && isInBounds(toROW, toCOL))
						{	
							moves[(*moveCount)++] = (struct MoveSet){ROW, COL, toROW, toCOL};
							break;	
						}
						else if(board[toROW][toCOL].color == color)
							break;
						
						toROW += dy[i];
						toCOL += dx[i];
					}
				}
			}
}

// Checks for all valid bishop moves on the board
void validBishopMoves(struct MoveSet moves[], int *moveCount, int color)
{
	int dx[] = {1, -1, 1, -1};
	int dy[] = {1, -1, -1, 1};	
	
	for(int ROW = 0; ROW < BOARD_SIZE; ROW++)
		for(int COL = 0; COL < BOARD_SIZE; COL++)
			if(board[ROW][COL].type == 'B' && board[ROW][COL].color == color)
			{
				for(int i = 0; i < 4; i++)
				{
					int toROW = ROW + dy[i];
					int toCOL = COL + dx[i];
					for(int j = 0; j < 8; j++)
					{
						if(board[toROW][toCOL].color == EMPTY && isInBounds(toROW, toCOL))
							moves[(*moveCount)++] = (struct MoveSet){ROW, COL, toROW, toCOL};	
						else if(board[toROW][toCOL].color == ((color == WHITE) ? BLACK : WHITE) && isInBounds(toROW, toCOL))
						{	
							moves[(*moveCount)++] = (struct MoveSet){ROW, COL, toROW, toCOL};
							break;	
						}
						else if(board[toROW][toCOL].color == color)
							break;
						
						toROW += dy[i];
						toCOL += dx[i];
					}
				}
			}
}

// Checks for all valid queen moves on the board
void validQueenMoves(struct MoveSet moves[], int *moveCount, int color)
{
	int dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
	int dy[] = {1, -1, -1, 1, 0, 0, 1, -1};	
	
	for(int ROW = 0; ROW < BOARD_SIZE; ROW++)
		for(int COL = 0; COL < BOARD_SIZE; COL++)
			if(board[ROW][COL].type == 'Q' && board[ROW][COL].color == color)
			{
				for(int i = 0; i < 8; i++)
				{
					int toROW = ROW + dy[i];
					int toCOL = COL + dx[i];
					for(int j = 0; j < 8; j++)
					{
						if(board[toROW][toCOL].color == EMPTY && isInBounds(toROW, toCOL))
							moves[(*moveCount)++] = (struct MoveSet){ROW, COL, toROW, toCOL};	
						else if(board[toROW][toCOL].color == ((color == WHITE) ? BLACK : WHITE) && isInBounds(toROW, toCOL))
						{	
							moves[(*moveCount)++] = (struct MoveSet){ROW, COL, toROW, toCOL};
							break;	
						}
						else if(board[toROW][toCOL].color == color)
							break;
						
						toROW += dy[i];
						toCOL += dx[i];
					}
				}
			}
}

// Checks for all valid king moves on the board
void validKingMoves(struct MoveSet moves[], int *moveCount, int color)
{	
	int dx[] = {1, -1, 1, -1, 1, -1, 0, 0};
	int dy[] = {1, -1, -1, 1, 0, 0, 1, -1};	
	
	for(int ROW = 0; ROW < BOARD_SIZE; ROW++)
		for(int COL = 0; COL < BOARD_SIZE; COL++)
			if(board[ROW][COL].type == 'K' && board[ROW][COL].color == color)
			{
				for(int i = 0; i < 8; i++)
				{
					if(board[ROW+dy[i]][COL+dx[i]].color == EMPTY && isInBounds(ROW+dy[i], COL+dx[i]))
						moves[(*moveCount)++] = (struct MoveSet){ROW, COL, ROW+dy[i], COL+dx[i]};	
					else if(board[ROW+dy[i]][COL+dx[i]].color == ((color == WHITE) ? BLACK : WHITE) && isInBounds(ROW+dy[i], COL+dx[i]))
					{	
						moves[(*moveCount)++] = (struct MoveSet){ROW, COL, ROW+dy[i], COL+dx[i]};
						break;	
					}
					else if(board[ROW+dy[i]][COL+dx[i]].color == color)
						break;
				}
			}
}

int main()
{
	struct MoveSet moves[500];
	int moveCount = 0;
	int currentPlayerColor = WHITE;

	printBoard();
	validPawnMoves(moves, &moveCount, currentPlayerColor);
	validKnightMoves(moves, &moveCount, currentPlayerColor);
	validBishopMoves(moves, &moveCount, currentPlayerColor);
	validRookMoves(moves, &moveCount, currentPlayerColor);
	validQueenMoves(moves, &moveCount, currentPlayerColor);
	validKingMoves(moves, &moveCount, currentPlayerColor);

	for(int i = 0; i < moveCount; i++)
	{
		printf("(%d) %d %d -> %d %d\n", i+1, moves[i].ROW, moves[i].COL, moves[i].toROW, moves[i].toCOL);
	}



}
