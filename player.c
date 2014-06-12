#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "define.h"
#include "player.h"

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

void seikunPlay(Player* p) {

  Board* board = p->board;
  int i = 0;
  for (i = 0; i < 9; i++){
    if(board->state[i] == BLANK_MOVE){
      board->state[i] = X_MOVE;
      if(findWinner(board)){
        board->state[i] = BLANK_MOVE;
        playMove(board, p->piece, i);
        return;
      }
      board->state[i] = O_MOVE;
      if(findWinner(board)){
        board->state[i] = BLANK_MOVE;
        playMove(board, p->piece, i);
        return;
      }
      board->state[i] = BLANK_MOVE;
    }
  }

  int position = rand() % 9;

  while(!isValidMove(board, p->piece, position)) {
    position = rand() % 9;
  }

  playMove(board, p->piece, position);
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
    case PTYPE_SEIKUNATOR:
      p->play = &seikunPlay;
    default:
      // This should never happen
      // Exit gracefully or something? idk
      break;
  }
}
