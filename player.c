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
    position = (position + 1) % 9;
  }

  playMove(board, p->piece, position);
}

void learningPlay(Player* p) {
}

void initPlayer(Player* p, Board* b, p_type type, char piece) {
  p->board = b;
  p->piece = piece;

  switch (type) {
    case PTYPE_HUMAN:
      p->play = &humanPlay;
      break;
    case PTYPE_RANDOM:
      srand(time(NULL));

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
