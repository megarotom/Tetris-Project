#include <ncurses.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "Game.hpp"

Game::Game(int boardWidth, int boardHeight, WINDOW *game, WINDOW *stats, WINDOW *inst)
    : board(boardWidth, boardHeight),
      currentTetrimino(generateTetrimino()),
      nextTetrimino(generateTetrimino()),
      score(0),
      level(1),
      linesCleared(0),
      dropSpeed(1000) {
    srand(time(0));
    gameBoard = game;
    statsBoard = stats;
    instBoard = inst;
}

void Game::run() {
//    // Initialize the ncurses screen
//    initscr();
//    raw();
//    timeout(dropSpeed);
//    noecho();
//    curs_set(0);
//    keypad(stdscr, TRUE);
//    start_color();
    currentTetrimino = generateTetrimino();
    nextTetrimino = generateTetrimino();
    werase(gameBoard);
    start_color();
    wborder(gameBoard, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_S1,
            ACS_ULCORNER, ACS_URCORNER, ACS_S1, ACS_S1);
    board.draw(gameBoard);
    currentTetrimino->draw(1,1,gameBoard);
    drawInstructions(instBoard);
    drawStats(statsBoard);
//        drawLevel(1, 15, statsBoard);
    wrefresh(gameBoard);


    // Main game loop
    while (true) {
//        int input = getch();
        int input = 259;
        if (input != ERR) {
            handleInput(input);
        }

        if (!board.collidesWith(*currentTetrimino)) {
            currentTetrimino->move(0, 1);
        } else {
            board.merge(*currentTetrimino);
            int lines = board.clearLines();
            linesCleared += lines;
            score += lines * 100;
            level = linesCleared / 10 + 1;
            dropSpeed = 1000 - (level - 1) * 100;
            timeout(dropSpeed);

            currentTetrimino = std::move(nextTetrimino);
            nextTetrimino = generateTetrimino();

            if (board.collidesWith(*currentTetrimino)) {
                break; // Game over
            }
        }
//        werase(gameBoard);
        start_color();
        wborder(gameBoard, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_S1,
                ACS_ULCORNER, ACS_URCORNER, ACS_S1, ACS_S1);
        board.draw(gameBoard);
        currentTetrimino->draw(currentTetrimino->getX(), currentTetrimino->getY(), gameBoard);
//        nextTetrimino->draw(1, 1, gameBoard);
        drawInstructions(instBoard);
        drawStats(statsBoard);
//        drawLevel(1, 15, statsBoard);
        wrefresh(gameBoard);
    }

    // End the game
    endwin();
}

void Game::handleInput(int input) {
    switch (input) {
        case KEY_LEFT:
            if (!board.collidesWith(*currentTetrimino->cloneMoved(-1, 0))) {
                currentTetrimino->move(-1, 0);
            }
            break;
        case KEY_RIGHT:
            if (!board.collidesWith(*currentTetrimino->cloneMoved(1, 0))) {
                currentTetrimino->move(1, 0);
            }
            break;
        case KEY_DOWN:
            if (!board.collidesWith(*currentTetrimino->cloneMoved(0, 1))) {
                currentTetrimino->move(0, 1);
            }
            break;
        case KEY_UP:
            currentTetrimino->rotate();
            if (board.collidesWith(*currentTetrimino)) {
                currentTetrimino->rotateBack();
            }
            break;
    }
}

std::unique_ptr<Tetrimino> Game::generateTetrimino() {
    int randomNumber = rand() % 7;
    int type = randomNumber;
    return std::unique_ptr<Tetrimino>(new Tetrimino(type));
}


void Game::drawInstructions(WINDOW *win) const {
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Instructions:");
    mvwprintw(win, 1 + 1, 2, "Left: Move left");
    mvwprintw(win, 1 + 2, 2, "Right: Move right");
    mvwprintw(win, 1 + 3, 2, "Down: Move down");
    mvwprintw(win, 1 + 4, 2, "Up: Rotate");
    wrefresh(win);

}

void Game::drawStats(WINDOW *win) const {
    box(win, 0 ,0);
    mvwprintw(win, 1, 2, "Score: %d", score);
    mvwprintw(win, 2, 2, "Level: %d", level);
    wrefresh(win);
}

void Game::drawLevel(int x, int y, WINDOW* win) const {
    box(win, 0 ,0);
    mvwprintw(win, y, x, "Level:");
    mvwprintw(win, y + 1, x, "%d", level);
    wrefresh(win);
}
