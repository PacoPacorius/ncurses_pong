/* TODO!
 * 1. Keep track of where paddles are by storing the position of their top character -done
 * 2. Make any paddle movement happen (draw and delete) -done
 * 3. Make only legal paddle movements happen -done
 * 4. Accept both inputs at once
 * * 4.1. If getch() returns anything other than ERR, set a boolean to 1, indicating keypress and hold
 * * 4.2. If getch() returns ERR, set a boolean to 0, indicating key depress
 * * 4.3. Only move paddles if the boolean is set to 0              
 *
 * This is good, but one of the two players can still hog the input
 *
 * 1. Print a ball
 * 2. Move the ball
 * 3. Ball physics!
 * 4. Logic for when ball goes out of bounds
 */
#include <ncurses.h>

#define PADDLE_SIZE LINES / 5

void init_ncurses();
int input(int *paddley1, int *paddley2, int* previous_char);
void update_paddle_positions(int paddley1, int paddley2);

int main(){

// initialisation functions
//====================================================================================================================================================================================//
    int i = 0;      // counter var

    init_ncurses();
    for(i = 0; i < COLS; i++){
        mvwaddch(stdscr, 2, i, '-');
        mvwaddch(stdscr, LINES - 1, i, '-');
    }
//====================================================================================================================================================================================//
// var declarations
    int paddley1 = 5; // initial values for the paddles
    int paddley2 = 5;
    int loop_control = 0;
    int previous_char = ERR; // previous char from getch(), checks for ERR

//====================================================================================================================================================================================//
    

    for(i = 0; i < PADDLE_SIZE; i++)
        mvwaddch(stdscr, paddley1 + i, 2, ACS_BLOCK); // paddle 1
    for(i = 0; i < PADDLE_SIZE; i++)
        mvwaddch(stdscr, paddley2 + i, COLS - 2, ACS_BLOCK); // paddle 2

   while(loop_control == 0){
        loop_control = input(&paddley1, &paddley2, &previous_char); // input returns 1 if exiting
        update_paddle_positions(paddley1, paddley2);
        refresh();
    }
    getch();
    endwin();
    return 0;
}

void init_ncurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

}

int input(int *paddley1, int *paddley2, int *previous_char){
    int c = getch();

    if(*previous_char == ERR){
        switch(c){
        case 'w':                           // up and down movements for paddle1
            if(*paddley1 > 3){
                *paddley1 = *paddley1 - 1;
            }
            break;
        case 's':
            if(*paddley1 < LINES - 1 - PADDLE_SIZE){
                *paddley1 = *paddley1 + 1;
            }
            break;
        case KEY_UP:                        // up and down movements for paddle2
            if(*paddley2 > 3)
                *paddley2 = *paddley2 - 1;
            break;
        case KEY_DOWN:
            if(*paddley2 < LINES - 1 - PADDLE_SIZE)
                *paddley2 = *paddley2 + 1;
            break;
        case 'q':
            return 1;
        }
    }

    *previous_char = c;
    return 0;
}

void update_paddle_positions(int paddley1, int paddley2){
    // erase previous paddle positions
    int i;
    for(i = 3; i < LINES - 1; i++){
        mvwaddch(stdscr, i, 2, ' ');            // erase paddle1
        mvwaddch(stdscr, i, COLS - 2, ' ');     // erase paddle2
    }

    for(i = 0; i < PADDLE_SIZE; i++)
        mvwaddch(stdscr, paddley1 + i, 2, ACS_BLOCK); // paddle 1
    for(i = 0; i < PADDLE_SIZE; i++)
        mvwaddch(stdscr, paddley2 + i, COLS - 2, ACS_BLOCK); // paddle 2

}
