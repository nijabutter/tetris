#include <iostream>
#include <ncurses.h>
#include "Tetromino.hpp"

int main() {
    
    int game[GAME_HEIGHT][GAME_WIDTH] = {0};
    Tetromino piece = Tetromino(game);
    piece.reset();
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    cbreak();
    wtimeout(stdscr, 500);
    curs_set(0);
    
    use_default_colors();
    start_color();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_RED, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_BLUE, -1);
    init_pair(7, COLOR_WHITE, -1);
    
    int input;
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int offset_top = (screen_height - GAME_HEIGHT) / 2;
    int offset_left = screen_width/2 - GAME_WIDTH;
    bool paused = false;
    do {
    	erase();
        // top border
        move(offset_top-1, offset_left-1);
        addch(ACS_ULCORNER);
        for (int i = 0; i < GAME_WIDTH; i++) {
            addch(ACS_HLINE);
            addch(ACS_HLINE);
        }
        addch(ACS_URCORNER);

        for (int i = 0; i < GAME_HEIGHT; i++) {
			move(i+offset_top, offset_left-1);
            addch(ACS_VLINE);
            for (int j = 0; j < GAME_WIDTH; j++) {
                
                if (game[i][j] == 0) {
                    addch(' ');
                    addch(' ');
                    //printw("%d", game[i*j]);
                } else {
                    switch (game[i][j]) {
                        case 'I': {
                            attron(COLOR_PAIR(1));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(1));
                        }break;
                        case 'O': {
                            attron(COLOR_PAIR(2));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(2));
                        }break;
                        case 'T': {
                            attron(COLOR_PAIR(3));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(3));
                        }break;
                        case'S': {
                            attron(COLOR_PAIR(4));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(4));
                        }break;
                        case 'Z': {
                            attron(COLOR_PAIR(5));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(5));
                        }break;
                        case 'J': {
                            attron(COLOR_PAIR(6));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(6));
                        }break;
                        case 'L': {
                            attron(COLOR_PAIR(7));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(7));
                        } break;
                        default: {
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                        }break;
                    }
                }
            }
            addch(ACS_VLINE);

        }
        move(offset_top+GAME_HEIGHT, offset_left-1);
        addch(ACS_LLCORNER);
        for (int i = 0; i < GAME_WIDTH; i++) {
            addch(ACS_HLINE);
            addch(ACS_HLINE);
        }
        addch(ACS_LRCORNER);
        
        int ghost_y = piece.get_ghost_y();
        for (int i = 0; i < piece.get_shape_size(); i++) {
            move(ghost_y+i+offset_top, piece.x*2+offset_left);
            for (int j = 0; j < piece.get_shape_size(); j++) {
                if (piece.shape[i][j] == 1) {
                    addch(ACS_BOARD);
                    addch(ACS_BOARD);
                } else {
                    int y, x;
                    getyx(stdscr, y, x);
                    move(y, x+2);
                }
            }
        }

        for (int i = 0; i < piece.get_shape_size(); i++) {
            move(piece.y+i+offset_top, piece.x*2+offset_left);
            for (int j = 0; j < piece.get_shape_size(); j++) {
                if (piece.shape[i][j] == 1) {
                    switch (piece.get_type()) {
                        case 'I': {
                            attron(COLOR_PAIR(1));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(1));
                        }break;
                        case 'O': {
                            attron(COLOR_PAIR(2));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(2));
                        }break;
                        case 'T': {
                            attron(COLOR_PAIR(3));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(3));
                        }break;
                        case'S': {
                            attron(COLOR_PAIR(4));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(4));
                        }break;
                        case 'Z': {
                            attron(COLOR_PAIR(5));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(5));
                        }break;
                        case 'J': {
                            attron(COLOR_PAIR(6));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(6));
                        }break;
                        case 'L': {
                            attron(COLOR_PAIR(7));
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                            attroff(COLOR_PAIR(7));
                        } break;;
                        default: {
                            addch(ACS_BLOCK);
                            addch(ACS_BLOCK);
                        }break;
                    }
                } else {
                    int y, x;
                    getyx(stdscr, y, x);
                    move(y, x+2);
                }
                //printw("%d", piece.shape[i*DEFAULT_SHAPE_SIZE+j]);
            }
        }
        input = getch();
        if (paused) {
            if (input == 'p')
                paused = !paused;
        }
        else {
            switch(input) {
                case 'r': {
                    piece.rotate();
                } break;
                case KEY_RIGHT: {
                    piece.move_right();
                } break;
                case KEY_LEFT: {
                    piece.move_left();
                } break;
                case KEY_UP: {
                    piece.move_up();
                } break;
                case KEY_DOWN: {
                    piece.move_down();
                } break;
                case 'p': {
                    paused = !paused;
                } break;
                case ' ': {
                    while (piece.move_down())
                        continue;
                    piece.place();
                    piece.reset();
                }break;
                default: break;
            }
            if (!piece.move_down()) {
                // collision - new piece
                piece.place();
                piece.reset();
            }
        }
        refresh();

    } while (input != 'q');
    erase();
    endwin();
}
