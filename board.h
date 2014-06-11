#ifndef _BOARD_H_
#define _BOARD_H_

#define BRAIN_SIZE 1048575
#define BOARD_X_POS 4
#define BOARD_Y_POS 9

typedef struct _knowledge {
  int experience[9];
  int wins[9];
  int instances;
} Knowledge;

typedef struct _move {
  int encodedState;
  int position;
  char player;
} Move;

typedef struct _board {
	char state[9];
	char playerturn;

  Knowledge* brain;
  Move history[9];
  int turn;
} Board;

void initKnowledge(Board *board);
int encodeBoardState(Board *board, char player_piece);
void initBoard(Board *board, char player_start);
void saveKnowledge(Board *board, char winner);
int findWinner(Board *board);
int isValidMove(Board *board, char piece, int position);
void playMove(Board *board, char piece, int position);

#endif
