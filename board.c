#include <curses.h>
#include <stdio.h>

#include "board.h"
#include "define.h"

void initBoard(Board *board, char player_start) {
	int i;

	for (i = 0; i < TOTAL_MOVES; i++) {
		board->state[i] = BLANK_MOVE;
	}

  board->firstMove = player_start;
	board->playerturn = player_start;
  board->turn = 0;

  move(BOARD_Y_POS - 1, BOARD_X_POS - 4);
	printw("      |   |   \n");
	printw("      |   |   \n");
	printw("      |   |   \n");
	printw("   ---+---+---\n");
	printw("      |   |   \n");
	printw("      |   |   \n");
	printw("      |   |   \n");
	printw("   ---+---+---\n");
	printw("      |   |   \n");
	printw("      |   |   \n");
	printw("      |   |   \n\n\n");
}

int magicSquareCheck(Board *board, char player) {
  const int magicSquare[9] = {8, 1, 6, 3, 5, 7, 4, 9, 2};

  return 0;
}

int findWinner(Board *board) {
  if (board->turn < 5) {
    return -1;
  }

  return 0;
}

int isValidMove(Board *board, char piece, int position) {
	return board->state[position] == BLANK_MOVE &&
         board->playerturn == piece;
}

int encodeBoardState(Board *board) {
  int encoding = 0;

  int i;
  for (i = 0; i < 9; i++) {
    if (board->state[i] != BLANK_MOVE) {
      if (board->state[i] == board->firstMove) {
        encoding += (1 << i);
      } else {
        encoding += (1 << (9 + i));
      }
    }
  }

  return encoding;
}

void playMove(Board *board, char piece, int position) {
  board->history[board->turn].encodedState = encodeBoardState(board);
  board->history[board->turn].position = position;
  board->history[board->turn].player = piece;

	board->state[position] = piece;
  if (piece == X_MOVE) {
    board->playerturn = O_MOVE;
  } else {
    board->playerturn = X_MOVE;
  }

  move(BOARD_Y_POS + ((position / 3) << 2), BOARD_X_POS + ((position % 3) << 2));
  printw("%c", piece);

  board->turn++;
}

