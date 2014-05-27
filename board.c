#include <stdio.h>

#include "board.h"
#include "define.h"

void initBoard(Board *board, int player_start) {
	int i;

	for(i = 0; i < TOTAL_MOVES; i++) {
		board->state[i] = BLANK_MOVE;
	}

	board->playerturn = player_start;
}


int isValidMove(Board *board, int piece, int position) {
	return board->state[position] == BLANK_MOVE &&
         board->playerturn == piece;
}

void playMove(Board *board, int piece, int position) {
	board->state[position] = piece;
	board->playerturn = (board->playerturn % 2) + 1;
}

void printBoard(Board *board) {
	moveCursor(10,10);
	printf("win");
}
