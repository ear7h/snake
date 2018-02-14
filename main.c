#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "board.h"
#include "console.h"


enum direction {
    B_UP, B_DOWN, B_LEFT, B_RIGHT
};


int ALIVE = 1;

int point_compare(point p1, point p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

point APPLE = {.x = 4, .y = 0};

typedef struct snake_t {
    point *snake;
    uint8_t length;
    uint8_t head;
    enum direction dir;
} snake_t;

void tick_snake(snake_t *snake) {
    point next = snake->snake[snake->head];

    switch (snake->dir) {
        case B_UP:
            next.y = (next.y - 1 + BOARD_Y) % BOARD_Y; // prevent negatives
            break;
        case B_DOWN:
            next.y = (next.y + 1) % BOARD_Y;
            break;
        case B_LEFT:
            next.x = (next.x - 1 + BOARD_X) % BOARD_X; // prevent negatives
            break;
        case B_RIGHT:
            next.x = (next.x + 1) % BOARD_X;
            break;
    }

    if (point_compare(next, APPLE)) {
        // create new snake array
        point *new = calloc(snake->length + 1, sizeof(point));

        // copy
        for (int i = 0; i < snake->length; i++) {
            new[i] = snake->snake[(snake->head + i + 1) % snake->length];
        }
        new[snake->length] = next;

        // update snake in memory
        free(snake->snake);
        snake->snake = new;
        snake->head = snake->length;
        snake->length++;

        // update apple location
        APPLE.x = rand() % BOARD_X;
        APPLE.y = rand() % BOARD_Y;

    } else {
        // move head cursor to oldest element
        snake->head++;
        snake->head %= snake->length;

        // replace the last element
        snake->snake[snake->head] = next;
    }
}


void print_snake(snake_t snake) {

    print_on_board(APPLE, "O");

    point head = snake.snake[snake.head];
    print_on_board(head, "@");

    point seg;

    for (int i = 1; i < snake.length; i++) {
        seg = snake.snake[(snake.head + i) % snake.length];
        if (point_compare(head, seg)) {
            print_on_board(head, "x");
            ALIVE = 0;
            return;
        }

        print_on_board(seg, "#");
    }
}

void *snake_control(void *snake_ptr) {
    snake_t *snake = (snake_t *) snake_ptr;

    while (ALIVE) {
        // check for escape code
        if (getch() == 27) {

            // gets the next char
            // if esc again then exit
            // if not '[' ignore
            if (getch() != 91) {
                continue;
            };

            // now handle arrows
            switch (getch()) {
                case 'A':
                    snake->dir = B_UP;
                    break;
                case 'B':
                    snake->dir = B_DOWN;
                    break;
                case 'C':
                    snake->dir = B_RIGHT;
                    break;
                case 'D':
                    snake->dir = B_LEFT;
                    break;
                default:
                    continue;
            }
        } else { // handle asdw
            switch (getch()) {
                case 'A':
                case 'a':
                    snake->dir = B_LEFT;
                    break;
                case 'S':
                case 's':
                    snake->dir = B_DOWN;
                    break;
                case 'D':
                case 'd':
                    snake->dir = B_RIGHT;
                    break;
                case 'W':
                case 'w':
                    snake->dir = B_UP;
                    break;
                default:
                    continue;
            }
        }
    }

    return NULL;
}

long hz_to_ns(int hz) {
    return ((long)1e+9 - 1) / hz;
}

int main() {
    clear_console();

    build_board();

    snake_t snake = {
            .snake = calloc(1, sizeof(point)),
            .length = 1,
            .dir = B_RIGHT,

    };

    pthread_t key_controls;

    if (pthread_create(&key_controls, NULL, snake_control, &snake)) {
        print_at(1, 1, "could not listen to keyboard");
        return 1;
    }

    // timing
    struct timespec t1, t2;

    char *score = malloc(4 * sizeof(char)); //2 digit number + \0

    while (ALIVE) {
        clear_game_board();

        print_snake(snake);
        tick_snake(&snake);

        // needs newline or print_snake() shit goes wack
        sprintf(score, "%d\n", snake.length);
        print_at(0, BOARD_Y + 2, score);

        /*
         * robert jordan - wheel of time
         */

        // set the refresh time
        t1.tv_sec = 0;
        t1.tv_nsec = hz_to_ns(snake.length + 1); // start at 2 hz

        while (nanosleep(&t1, &t2) == -1) {
            if (errno == EINTR) {
                printf("s: %ld, ns: %ld\n", t1.tv_sec, t1.tv_nsec);
                t1 = t2;
            } else {
                printf("error %d", errno);
                return 1;
            }
        }
    }


    if (pthread_kill(key_controls, SIGINT)) {
        print_at(1, 1, "error joining threads");
        return 1;
    }

    free(snake.snake);
    free(score);

    move_cursor(0, BOARD_Y + 3);
    printf("end score: %d\n", snake.length);
    clear_stdin();
    printf("press any key and enter to exit\n");
    getchar();

    return 0;
}
