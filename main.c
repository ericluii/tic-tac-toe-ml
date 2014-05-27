#include <ctype.h>
#include <curses.h>
#include <stdio.h>

#include "board.h"
#include "define.h"
#include "main.h"

void initScreen(WINDOW *w) {
	cbreak();
	nodelay(w, true);
	noecho();

	printw("Tic-Tac-Toe Machine Learning Demo - By Eric Lui\n");
	printw("===============================================\n\n");
	printw("Game Number: 1\n\n");
	printw("Game State\n");
	printw("================================\n\n");
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
	printw(">");
}

int main(void) {
	Board game;
	char c = ERR;
	char cmd_buffer[32];
	int cmd_buffer_size = 0;
	int game_number = 1;
	WINDOW *w = initscr();

	cmd_buffer[0] = '\0';

	initScreen(w);
	initBoard(&game, 1);

	FOREVER {
		if (c == ERR &&
				(c = getch()) != ERR) {
			if (c == KEYBOARD_BACKSPACE) {
				move(21, cmd_buffer_size);
				cmd_buffer[--cmd_buffer_size] = '\0';
				delch();
			} else if (c == KEYBOARD_RETURN) {
				printw("dog");
			} else if (isalnum(c)) {
				cmd_buffer[cmd_buffer_size++] = c;
				cmd_buffer[cmd_buffer_size] = '\0';

				move(21, cmd_buffer_size);
				printw("%c", c);
			}

			c = ERR;
		}
	}

	return 0;
}
