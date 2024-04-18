#include <stdio.h>
#include <ctype.h>

struct piece
{
	int color;
	char type;
};

enum pieceData
{
	EMPTY,	//0
	WHITE,	//1
	BLACK,	//2
	PAWN,	//3
	KNIGHT,	//4
	BISHOP,	//5
	ROOK,	//6
	QUEEN,	//7
	KING	//8
};

struct piece board[8][8] = {
{{2,'R'},{2,'N'},{2,'B'},{2,'Q'},{2,'K'},{2,'B'},{2,'N'},{2,'R'}},
{{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'},{2,'P'}},
{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
{{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'},{0,'_'}},
{{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'},{1,'P'}},
{{1,'R'},{1,'N'},{1,'B'},{1,'Q'},{1,'K'},{1,'B'},{1,'N'},{1,'R'}}
};

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

	printf("%d %d %d %d", y1, x1, y2, x2);
}

int main()
{
	printBoard();
	parser();
}
