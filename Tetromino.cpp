#include <stdlib.h>
#include <time.h>
#include "Tetromino.hpp"

Tetromino::Tetromino(int (*game)[GAME_WIDTH])
:game(game) {
    srand(time(NULL));
}

int Tetromino::get_ghost_y() {
    int old_y = y;
    while (is_valid_move(0, 1)) {
        y++;
    }
    int ghost_y = y;
    y = old_y;
    return ghost_y;
}

void Tetromino::reset() {
    x = (GAME_WIDTH - shape_size) / 2;
    y = 0;
    set_type(choices[rand() % sizeof(choices)/sizeof(choices[0])]);
    while (get_type() == '\0')
        set_type(choices[rand() % sizeof(choices)/sizeof(choices[0])]);
}

void Tetromino::set_type(const char letter) {
    type = letter;
    // I, O, T, S, Z, J, and L. 
    for (int i = 0; i < DEFAULT_SHAPE_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SHAPE_SIZE; j++) {
            shape[i][j] = 0;
        }
    }
    switch (type) {
        case 'I': {
            shape_size = 4;
            shape[1][0] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
            shape[1][3] = 1;
        } break;
        case 'O': {
            shape_size = 2;
            shape[0][0] = 1;
            shape[0][1] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
        }break;
        case 'T': {
            shape_size = 3;
            shape[0][1] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
        } break;
        case 'S': {
            shape_size = 3;
            shape[0][1] = 1;
            shape[0][2] = 1;
            shape[1][0] = 1;
            shape[1][1] = 1;
        }break;
        case 'Z': {
            shape_size = 3;
            shape[0][0] = 1;
            shape[0][1] = 1;
            shape[1][1] = 1;
            shape[1][2] = 1;
        }break;
        case 'J': {
            shape_size = 3;
            shape[0][1] = 1;
            shape[1][1] = 1;
            shape[2][0] = 1;
            shape[2][1] = 1;
        }break;
        case 'L': {
            shape_size = 3;
            shape[0][1] = 1;
            shape[1][1] = 1;
            shape[2][1] = 1;
            shape[2][2] = 1;
        }break;
        default: break;
    }
}

void Tetromino::rotate() {
    int temp_array[DEFAULT_SHAPE_SIZE][DEFAULT_SHAPE_SIZE] = {0};
    
    // transverse
    for (int i = 0; i < shape_size; i++) {
        for (int j=i; j < shape_size; j++) {
            temp_array[i][j] = shape[i][j]; // copy to temp array
            int temp = shape[i][j];
            shape[i][j] = shape[j][i];
            shape[j][i] = temp;
        }
    }
    // flip
    for (int i = 0; i < shape_size; i++) {
        for (int j = 0; j <(shape_size/2); j++) {
            int temp = shape[i][j];
            shape[i][j] = shape[i][shape_size-1-j];
            shape[i][shape_size-1-j] = temp;
        }
    }
    if (!is_valid_move(0, 0)) {
        // invalid rotate - go back
        for (int i = 0; i < shape_size; i++) {
            for (int j = 0; j < shape_size; j++) {
                shape[i][j] = temp_array[i][j];
            }
        }
    }
}

void Tetromino::move_right() {
    if (is_valid_move(1, 0))
        x++;
}

void Tetromino::move_left() {
    if (is_valid_move(-1, 0))
        x--;
}
bool Tetromino::move_down() {
    if (is_valid_move(0, 1)) {
        y++;
        return true;
    }
    return false;
}

void Tetromino::move_up() {
    if (is_valid_move(0, -1))
        y--;
}
void Tetromino::place() {
    for (int i = 0; i < shape_size; i++) {
        for (int j = 0; j < shape_size; j++) {
            if (shape[i][j] == 0)
                continue;
            game[y+i][x+j] = type;
        }
    }
    for (int i = 0; i < GAME_HEIGHT; i++) {
        bool good = true;
        for (int j = 0; j < GAME_WIDTH; j++) {
            if (game[i][j] == 0) {
                good = false;
                break;
            }
        }
        if (good) {
            for (int k = i; k > 0; k--) {
                for (int l = 0; l < GAME_WIDTH; l++) {
                    game[k][l] = game[k-1][l];
                    game[k-1][l] = 0;
                }
            }
        }
    }
}
bool Tetromino::is_valid_move(int x_offset, int y_offset) {
    for (int i = 0; i < shape_size; i++) {
        for (int j = 0; j < shape_size; j++) {
            if (shape[i][j] == 0)
                continue;
            int new_y = y + i + y_offset;
            int new_x = x + j + x_offset;
            if (game[new_y][new_x] != 0 ||
                new_y >= GAME_HEIGHT ||
                new_x < 0 ||
                new_x >= GAME_WIDTH)
            {
                return false;
            }
        }
        
    }
    return true;
}