#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include "Board.hpp"
#include <ncurses.h>
#include "Tetrimino.hpp"

class Game {
public:
    Game(int boardWidth, int boardHeight, WINDOW *pSt, WINDOW *pWinSt, WINDOW *pSt1);
    void run();

private:
    void handleInput(int input);
    std::unique_ptr<Tetrimino> generateTetrimino();
    void drawInstructions(WINDOW *win) const;
    void drawStats(WINDOW *win) const;
    void drawLevel(int x, int y, WINDOW* win) const;

    Board board;
    std::unique_ptr<Tetrimino> currentTetrimino;
    std::unique_ptr<Tetrimino> nextTetrimino;
    int score;
    int level;
    int linesCleared;
    int dropSpeed;
    WINDOW* gameBoard;
    WINDOW* statsBoard;
    WINDOW* instBoard;
};

#endif // GAME_HPP
