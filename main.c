#include <ctype.h>
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
	int game_number = 1, isPlaying = 0;

	cmd_buffer[0] = '\0';
	initScreen(w);
	initBoard(&game, O_MOVE);
  move(CURSOR_POSITION, 1);

  initPlayer(&p1, &game, PTYPE_RANDOM, O_MOVE);
  initPlayer(&p2, &game, PTYPE_RANDOM, X_MOVE);
  turn = &p1;

  for (int i = 0; i < 4; i++) {
    p1.play(&p1);
    p2.play(&p2);
  }

	FOREVER {
    if (isPlaying) {
      turn->play(turn); 

      if (0) { // check if end game

      } else if (turn == &p1) {
        turn = &p2;
      } else {
        turn = &p1;
      }
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
