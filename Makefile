all:
	g++ -c *.cpp -g -Wall -lncurses && g++ *.o -lncurses -o tetris
