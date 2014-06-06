#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "board.h"

typedef enum _p_type {
  PTYPE_HUMAN, 
  PTYPE_RANDOM,
  PTYPE_LEARNING
} p_type;

typedef struct _player {
  void (*play)(struct _player*);
  Board* board;
  char piece;
} Player;

void initPlayer(Player* p, Board* b, p_type type, char piece);

#endif

