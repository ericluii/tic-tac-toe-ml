#include <ctype.h>
#include <unistd.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "define.h"
#include "main.h"
#include "player.h"

void initScreen(WINDOW *w) {
  cbreak();
  nodelay(w, true);
  noecho();

  printw("Tic-Tac-Toe Machine Learning Demo - By Eric Lui\n");
  printw("===============================================\n\n");
  printw("Game Number: 0\n\n");
  printw("Game State\n");
  printw("================================\n\n");

  move(21, 0);
  printw("Player 1 Wins: 0\n");
  printw("Player 2 Wins: 0\n");
  printw("Draws: 0\n");
  move(CURSOR_POSITION, 0);
  printw(">");
}

void initNewGame(Board* b, Player* p1, Player* p2, p_type p1_type, Player** turn, char* first_move) {
  initBoard(b, *first_move);
  initPlayer(p1, b, p1_type, O_MOVE);
  initPlayer(p2, b, PTYPE_LEARNING, X_MOVE);

  if (*first_move == O_MOVE) {
    *turn = p1;
    *first_move = X_MOVE;
  } else {
    *turn = p2;
    *first_move = O_MOVE;
  }
}

int main(void) {
  // Non-game related variables
  char c = ERR;
  char cmd_buffer[32];
  int cmd_buffer_size = 0;
  WINDOW *w = initscr();

  // Initilaize non-game
  cmd_buffer[0] = '\0';
  initScreen(w);
  move(CURSOR_POSITION, 1);

  // Game Variables
  Board game;
  Player p1, p2, *turn;
  int game_number = 0;
  char starting_player = O_MOVE;
  int train = 0, trainCount = 0, isPlaying;
  int winner;
  int p1_win = 0, p2_win = 0, draws = 0;
  p_type type = PTYPE_RANDOM;

  // Initialize some game variables
  initKnowledge(&game);

  if (train > 0) {
    trainCount = train - 1;
    initNewGame(&game, &p1, &p2, type, &turn, &starting_player);
    game_number++;
    isPlaying = 1;
    move(3, 13);
    printw("%d", game_number);
  }

  FOREVER {
    if (isPlaying) {
      turn->play(turn);

      if ((winner = findWinner(&game))) {
        if (winner == O_MOVE) {
          p1_win++;

          move(P1_WIN_POSITION, 15);
          printw("%d", p1_win);
        } else if (winner == X_MOVE) {
          p2_win++;

          move(P2_WIN_POSITION, 15);
          printw("%d", p2_win);
        } else {
          draws++;

          move(DRAW_POSITION, 7);
          printw("%d", draws);
        }

        saveKnowledge(&game, winner);

        if (trainCount) {
          trainCount--;
          refresh();
          usleep(10);
          initNewGame(&game, &p1, &p2, type, &turn, &starting_player);
          game_number++;
          move(3, 13);
          printw("%d", game_number);
        } else {
          isPlaying = 0;
        }
      } else {
        if (turn == &p1) {
          turn = &p2;
        } else {
          turn = &p1;
        }
      }

      move(CURSOR_POSITION, 1);
    } else if (c == ERR &&
               (c = getch()) != ERR) {
      if (c == KEYBOARD_BACKSPACE && cmd_buffer_size > 0) {
        move(CURSOR_POSITION, cmd_buffer_size);
        cmd_buffer[--cmd_buffer_size] = '\0';
        delch();
      } else if (c == KEYBOARD_RETURN) {
        if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_Q) {
          endwin();
          free(game.brain);
          exit(0);
        } else if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_C) {
          p1_win = 0;
          p2_win = 0;
          draws = 0;

          move(P1_WIN_POSITION, 15);
          clrtoeol();
          printw("0");
          move(P2_WIN_POSITION, 15);
          clrtoeol();
          printw("0");
          move(DRAW_POSITION, 7);
          clrtoeol();
          printw("0");
        } else if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_H) {
          type = PTYPE_HUMAN;
        } else if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_R) {
          type = PTYPE_RANDOM;
        } else if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_M) {
          type = PTYPE_LEARNING;
        } else if (cmd_buffer_size > 0 && !(cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_G)) {
          train = atoi(cmd_buffer);
        } else if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_G) {
          trainCount = train - 1;
          isPlaying = 1;
          initNewGame(&game, &p1, &p2, type, &turn, &starting_player);
          game_number++;

          move(3, 13);
          printw("%d", game_number);
        }

        //TODO: process command
        move(CURSOR_POSITION, 1);
        clrtoeol();
        cmd_buffer[0] = '\0';
        cmd_buffer_size = 0;
      } else if (isalnum(c)) {
        cmd_buffer[cmd_buffer_size++] = c;
        cmd_buffer[cmd_buffer_size] = '\0';

        move(CURSOR_POSITION, cmd_buffer_size);
        printw("%c", c);
      }

      c = ERR;
    }
  }

  // Should never get here
  return -1;
}
