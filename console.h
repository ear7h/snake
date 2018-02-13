//
// Created by Julio on 2/11/18.
//

#ifndef SNAKE_CONSOLE_H
#define SNAKE_CONSOLE_H

#include "board.h"

void clear_console();

void move_cursor(int, int);

void print_at(int, int, char *);

char getch();

void clear_stdin();

#endif //SNAKE_CONSOLE_H
