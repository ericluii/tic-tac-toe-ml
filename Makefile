XCC = gcc
CFLAGS = -c -I. -I/usr/local/opt/ncurses/include
LDFLAGS = -L/usr/local/opt/ncurses/lib -lncurses

all: ttt

# Helper Classes
board.o: board.c
	$(XCC) $(CFLAGS) board.c

# Main Stuff
main.o: main.c
	$(XCC) $(CFLAGS) main.c

ttt: main.o board.o
	$(XCC) $(LDFLAGS) -o tictactoe *.o
	chmod u+x tictactoe

clean:
	-rm -f *.o tictactoe
