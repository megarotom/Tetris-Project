#include "Game.hpp"

int main() {
    // Initialization code
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    timeout(0);
    curs_set(0);
    start_color();

// Create separate windows
    WINDOW* gameBoardWin = newwin(22, 22, 1, 2);
    WINDOW* statsWin = newwin(4, 19, 1, 30);
    WINDOW* instructionsWin = newwin(7, 25, 7, 30);



    Game game(22, 22, gameBoardWin, statsWin, instructionsWin);
    game.run();
    return 0;
}
