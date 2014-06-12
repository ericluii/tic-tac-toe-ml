#include <stdlib.h>
#include <time.h>

#include "define.h"
#include "Player.h"

void humanPlay(Player* p) {
}

void randomPlay(Player* p) {
  int position = rand() % 9;

  Board* board = p->board;

  while(!isValidMove(board, p->piece, position)) {
    position = rand() % 9;
  }

  playMove(board, p->piece, position);
}

void learningPlay(Player* p) {
  Board* board = p->board;
  int state = encodeBoardState(board, p->piece);

  int bestMove = -1;
  int bestValue = -2147483648;

  int i;
  for (i = 0; i < 9; i++) {
    if (board->brain[state].experience[i] > bestValue && isValidMove(board, p->piece, i)) {
      bestValue = board->brain[state].experience[i];
      bestMove = i;
    }
  }

  playMove(board, p->piece, bestMove);
}

void initPlayer(Player* p, Board* b, p_type type, char piece) {
  p->board = b;
  p->piece = piece;

  switch (type) {
    case PTYPE_HUMAN:
      p->play = &humanPlay;
      break;
    case PTYPE_RANDOM:
      p->play = &randomPlay;
      break;
    case PTYPE_LEARNING:
      p->play = &learningPlay;
      break;
    default:
      // This should never happen
      // Exit gracefully or something? idk
      break;
  }
}
