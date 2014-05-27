#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct _board {
	int state[9];
	int playerturn;
} Board;

void initBoard(Board *board, int player_start);
int isValidMove(Board *board, int piece, int position);
void playMove(Board *board, int piece, int position);
void printBoard(Board *board);

#endif
