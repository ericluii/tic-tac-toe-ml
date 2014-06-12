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

// int isWinningMove(Board *board, char player) {
//   int ms[9] = {8, 1, 6, 3, 5, 7, 4, 9, 2};

//   int i;
//   for (i = 0; i < 9; i++) {
//     if (board->state[i] != player) {
//       ms[i] = 0;
//     }
//   }

//   return ((ms[0] + ms[1] + ms[2] == 15) ||
//           (ms[3] + ms[4] + ms[5] == 15) ||
//           (ms[6] + ms[7] + ms[8] == 15) ||
//           (ms[0] + ms[3] + ms[6] == 15) ||
//           (ms[1] + ms[4] + ms[7] == 15) ||
//           (ms[2] + ms[5] + ms[8] == 15) ||
//           (ms[0] + ms[4] + ms[8] == 15) ||
//           (ms[6] + ms[4] + ms[2] == 15));
// }

// void seikunPlay(Player* p) {

//   Board* board = p->board;
//   int i = 0;
//   for (i = 0; i < 9; i++){
//     if(board->state[i] == BLANK_MOVE){
//       printf("%c", board->state[i]);
//       board->state[i] = X_MOVE;
//       if(isWinningMove(board, X_MOVE) || isWinningMove(board, O_MOVE)){
//         board->state[i] = BLANK_MOVE;
//         playMove(board, p->piece, i);
//         break;
//       }
//       board->state[i] = O_MOVE;
//       if(isWinningMove(board, X_MOVE) || isWinningMove(board, O_MOVE)){
//         board->state[i] = BLANK_MOVE;
//         playMove(board, p->piece, i);
//         break;
//       }
//     }
//   }

//   int position = rand() % 9;

//   while(!isValidMove(board, p->piece, position)) {
//     position = rand() % 9;
//   }

//   playMove(board, p->piece, position);
// }

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
    // case PTYPE_SEIKUNATOR:
    //   p->play = &seikunPlay;
    default:
      // This should never happen
      // Exit gracefully or something? idk
      break;
  }
}
