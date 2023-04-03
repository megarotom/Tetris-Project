#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Block.hpp"
#include <ncurses.h>
#include "Tetrimino.hpp"

class Board {
public:
    Board(int width, int height);

    bool collidesWith(const Tetrimino& tetrimino) const;
    void merge(const Tetrimino& tetrimino);
    int clearLines();

    int getWidth() const;
    int getHeight() const;

    void draw(WINDOW* win) const;

private:
    int width;
    int height;
    std::vector<std::vector<chtype> > grid;
};

#endif // BOARD_HPP
