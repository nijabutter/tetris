#pragma once

#define DEFAULT_SHAPE_SIZE 4
#define GAME_WIDTH 10
#define GAME_HEIGHT 20
#define VISIBLE_HEIGHT 20

struct Tetromino {
    
    Tetromino(int (*game)[GAME_WIDTH]);
    void set_type(const char letter);
    inline char get_type() { return type; }
    void rotate();
    void move_left();
    void move_right();
    void move_up();
    bool move_down();
    void reset();
    inline int get_shape_size() { return shape_size; }
    int x, y;
    int shape[DEFAULT_SHAPE_SIZE][DEFAULT_SHAPE_SIZE] = {0};
    
    void place();
    int get_ghost_y();
    private:
    bool is_valid_move(int x_offset, int y_offset);
    char type;
    int shape_size = DEFAULT_SHAPE_SIZE; // will change to either 3x3 or 2x2
    int (*game)[GAME_WIDTH];
    const char* choices = "IOTSZJL";
};
