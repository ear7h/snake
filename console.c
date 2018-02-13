//
// Created by Julio on 2/11/18.
//

#include <stdio.h>
#include <termios.h>

void clear_console() {
    printf("\033[2J");
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void print_at(int x, int y, char *c){
    printf("\033[%d;%dH%s", y, x, c);
}

// copy paste for input without [return]
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
