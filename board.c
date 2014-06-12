#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "define.h"

void initKnowledge(Board *board) {
  board->brain = malloc(sizeof(Knowledge) * BRAIN_SIZE);

  int i, j;
  for (i = 0; i < BRAIN_SIZE; i++) {
    for (j = 0; j < 9; j++) {
      board->brain[i].experience[j] = 0;
      board->brain[i].wins[j] = 0;
    }

    board->brain[i].instances = 0;
  }
}

void saveKnowledge(Board *board, int winner) {
  move(30, 0);

  int i;
  for (i = board->turn - 1; i >= 0; i--) {
    if (winner == -1) {
      board->brain[board->history[i].encodedState].experience[board->history[i].position]--;
    } else if (board->history[i].player == winner) {
      board->brain[board->history[i].encodedState].experience[board->history[i].position] += 5*i;
      board->brain[board->history[i].encodedState].wins[board->history[i].position]++;
    } else {
      board->brain[board->history[i].encodedState].experience[board->history[i].position] -= 5*i;
    }

    board->brain[board->history[i].encodedState].instances++;

    printw("Player: %c, Turn: %d, State: %d, Move: %d, Experience: %d, Wins: %d, Instances: %d\n", board->history[i].player, i, board->history[i].encodedState, board->history[i].position, board->brain[board->history[i].encodedState].experience[board->history[i].position], board->brain[board->history[i].encodedState].wins[board->history[i].position], board->brain[board->history[i].encodedState].instances);
  }

  clrtobot();
}

void initBoard(Board *board, char player_start) {
  int i;

  for (i = 0; i < TOTAL_MOVES; i++) {
    board->state[i] = BLANK_MOVE;
  }

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
  int ms[9] = {8, 1, 6, 3, 5, 7, 4, 9, 2};

  int i;
  for (i = 0; i < 9; i++) {
    if (board->state[i] != player) {
      ms[i] = 0;
    }
  }

  return ((ms[0] + ms[1] + ms[2] == 15) ||
          (ms[3] + ms[4] + ms[5] == 15) ||
          (ms[6] + ms[7] + ms[8] == 15) ||
          (ms[0] + ms[3] + ms[6] == 15) ||
          (ms[1] + ms[4] + ms[7] == 15) ||
          (ms[2] + ms[5] + ms[8] == 15) ||
          (ms[0] + ms[4] + ms[8] == 15) ||
          (ms[6] + ms[4] + ms[2] == 15));
}

int findWinner(Board *board) {
  if (board->turn < 5) {
    return 0;
  } else if (magicSquareCheck(board, X_MOVE)) {
    return X_MOVE;
  } else if (magicSquareCheck(board, O_MOVE)) {
    return O_MOVE;
  } else if (board->turn == 9) {
    return -1;
  }

  return 0;
}

int isValidMove(Board *board, char piece, int position) {
  return board->state[position] == BLANK_MOVE &&
         board->playerturn == piece;
}

int encodeBoardState(Board *board, char player_piece) {
  int encoding = 0;

  int i;
  for (i = 0; i < 9; i++) {
    if (board->state[i] != BLANK_MOVE) {
      if (board->state[i] == player_piece) {
        encoding += (1 << i);
      } else {
        encoding += (1 << (9 + i));
      }
    }
  }

  return encoding;
}

void playMove(Board *board, char piece, int position) {
  board->history[board->turn].encodedState = encodeBoardState(board, piece);
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

