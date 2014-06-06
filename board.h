#ifndef _BOARD_H_
#define _BOARD_H_

#define BOARD_X_POS 4
#define BOARD_Y_POS 9

typedef struct _move {
  int encodedState;
  int position;
  char player;
} Move;

typedef struct _board {
	char state[9];
  char firstMove;
	char playerturn;

  Move history[9];
  int turn;
} Board;

void initBoard(Board *board, char player_start);
int findWinner(Board *board);
int isValidMove(Board *board, char piece, int position);
void playMove(Board *board, char piece, int position);

#endif
