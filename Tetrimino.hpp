#ifndef TETRIMINO_HPP
#define TETRIMINO_HPP

#include "Block.hpp"
#include <vector>
#include <ncurses.h>
#include <memory>

class Tetrimino {
public:
    Tetrimino(int type);

    void rotate();
    void rotateBack();
    void move(int dx, int dy);
    void draw(int x, int y, WINDOW* win) const;
    static void drawBlock(WINDOW* win, int x, int y, int color);
    std::unique_ptr<Tetrimino> clone() const;
    std::unique_ptr<Tetrimino> cloneMoved(int dx, int dy) const;

    int getType() const { return type; }
    int getColor() const { return color; }
    const std::vector<Block>& getBlocks() const { return blocks; }
    int getX() const { return x; }
    int getY() const { return y; }

    int x, y;

private:
    void setColor();
    void setBlocks();

    int type;
    int color;
    std::vector<Block> blocks;
};

#endif // TETRIMINO_HPP
