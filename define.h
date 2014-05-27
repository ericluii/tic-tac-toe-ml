#define FOREVER for(;;)

#define moveCursor(x, y) printf("\033[%d;%dH", x, y);
#define KEYBOARD_BACKSPACE 127
#define KEYBOARD_RETURN 10 

#define BLANK_MOVE 0
#define X_MOVE 1
#define O_MOVE 2
#define TOTAL_MOVES 9
