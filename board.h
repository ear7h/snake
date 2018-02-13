//
// Created by Julio on 2/11/18.
//

#ifndef SNAKE_BOARD_H
#define SNAKE_BOARD_H

const int BOARD_X;
const int BOARD_Y;
const int BOARD_BORDER_SIZE;

typedef struct point {
    int x;
    int y;
} point;

void build_board();

void clear_game_board();

void print_on_board(point, char *);

#endif //SNAKE_BOARD_H
