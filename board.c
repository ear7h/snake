//
// Created by Julio on 2/11/18.
//
#include <stdio.h>

#include "console.h"

const int BOARD_X = 50;
const int BOARD_Y = 20;

const int BOARD_BORDER_SIZE = 1;

// ─│
//╭╮╰╯
void build_board() {
    // top row
    move_cursor(1, 1);

    printf("╭");
    for (int i = 0; i < BOARD_X; i++) {
        printf("─");
    }
    printf("╮");

    // side walls
    move_cursor(1, 2);
    for (int i = 2; i <= BOARD_Y + 1; i++) {
        print_at(1, i, "│");
        print_at(BOARD_X + 2, i, "│");
    }


    // bottom row
    move_cursor(0, BOARD_Y + 2);
    printf("╰");
    for (int i = 0; i < BOARD_X; i++) {
        printf("─");
    }
    printf("╯");
}


void clear_game_board() {
    for (int y = 1; y <= BOARD_Y; y++) {
        for (int x = 1; x <= BOARD_X; x++) {
            printf("\033[%d;%dH%s", y + BOARD_BORDER_SIZE, x + BOARD_BORDER_SIZE, " ");
        }
    }
}

// board coordinates start at 0 but console at 1
void print_on_board(point p, char *c) {
    printf("\033[%d;%dH%s", p.y + BOARD_BORDER_SIZE + 1, p.x + BOARD_BORDER_SIZE + 1, c);
}