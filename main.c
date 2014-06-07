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
  printw("Game Number: 1\n\n");
  printw("Game State\n");
  printw("================================\n\n");

  move(CURSOR_POSITION, 0);
  printw(">");
}

int main(void) {
  char c = ERR;
  char cmd_buffer[32];
  int cmd_buffer_size = 0;
  WINDOW *w = initscr();

  Board game;
  Player p1, p2, *turn;
  int game_number = 0, isPlaying = 0;

  cmd_buffer[0] = '\0';
  initScreen(w);
  move(CURSOR_POSITION, 1);

  FOREVER {
    if (isPlaying) {
      turn->play(turn);

      if (findWinner(&game)) {
        if (game_number < TOTAL_TRAINING) {
          initBoard(&game, O_MOVE);
          initPlayer(&p1, &game, PTYPE_RANDOM, O_MOVE);
          initPlayer(&p2, &game, PTYPE_RANDOM, X_MOVE);
          turn = &p1;
          game_number++;
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

      move(21, 1);
    } else if (c == ERR &&
               (c = getch()) != ERR) {
      if (c == KEYBOARD_BACKSPACE && cmd_buffer_size > 0) {
        move(21, cmd_buffer_size);
        cmd_buffer[--cmd_buffer_size] = '\0';
        delch();
      } else if (c == KEYBOARD_RETURN) {
        if (cmd_buffer_size == 1 && cmd_buffer[0] == KEYBOARD_Q) {
          endwin();
          exit(0);
        }

        isPlaying = 1;
        initBoard(&game, O_MOVE);
        initPlayer(&p1, &game, PTYPE_RANDOM, O_MOVE);
        initPlayer(&p2, &game, PTYPE_RANDOM, X_MOVE);
        turn = &p1;
        game_number++;

        //TODO: process command
        move(21, 1); 
        clrtoeol();
        cmd_buffer[0] = '\0';
        cmd_buffer_size = 0;
      } else if (isalnum(c)) {
        cmd_buffer[cmd_buffer_size++] = c;
        cmd_buffer[cmd_buffer_size] = '\0';

        move(21, cmd_buffer_size);
        printw("%c", c);
      }

      c = ERR;
    }
  }

  // Should never get here
  return -1;
}
