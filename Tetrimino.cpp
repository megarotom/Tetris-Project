#include "Tetrimino.hpp"
#include <algorithm>
#include <memory>
#include <utility>

Tetrimino::Tetrimino(int type) : type(type), x(0), y(0) {
    setColor();
    setBlocks();
}

void Tetrimino::setColor() {
    color = 1 + (type % 7);
}

std::unique_ptr<Tetrimino> Tetrimino::clone() const {
    return std::unique_ptr<Tetrimino>(new Tetrimino(*this));
}

std::unique_ptr<Tetrimino> Tetrimino::cloneMoved(int dx, int dy) const {
    auto cloned = clone();
    cloned->move(dx, dy);
    return cloned;
}

void Tetrimino::rotate() {
    for (Block& block : blocks) {
        int tempX = block.getX();
        block.setX(block.getY());
        block.setY(-tempX);
    }
}

void Tetrimino::rotateBack() {
    for (Block& block : blocks) {
        int tempY = block.getY();
        block.setY(block.getX());
        block.setX(-tempY);
    }
}


void Tetrimino::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Tetrimino::draw(int x, int y, WINDOW* win) const {
    for (const auto& block : blocks) {
        wattron(win, COLOR_PAIR(block.getColor()));
        mvwaddch(win, block.getY() + y, block.getX() + x, ACS_CKBOARD);
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_CYAN);
        init_pair(3, COLOR_BLUE, COLOR_BLUE);
        init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
        init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(6, COLOR_GREEN, COLOR_GREEN);
        init_pair(7, COLOR_RED, COLOR_RED);
        init_pair(8, COLOR_WHITE, COLOR_CYAN);
        wattroff(win, COLOR_PAIR(block.getColor()));
    }
}
void Tetrimino::drawBlock(WINDOW* win, int x, int y, int color) {
    wattron(win, COLOR_PAIR(color));
    mvwaddch(win, y, x, ACS_CKBOARD);
    wattroff(win, COLOR_PAIR(color));
}



void Tetrimino::setBlocks() {
    switch (type) {
        case 1: // I shape
            blocks = {Block(0, 1, color), Block(1, 1, color), Block(2, 1, color), Block(3, 1, color)};
            break;
        case 2: // L shape
            blocks = {Block(0, 0, color), Block(0, 1, color), Block(1, 1, color), Block(2, 1, color)};
            break;
        case 3: // J shape
            blocks = {Block(2, 0, color), Block(0, 1, color), Block(1, 1, color), Block(2, 1, color)};
            break;
        case 4: // O shape
            blocks = {Block(1, 0, color), Block(2, 0, color), Block(1, 1, color), Block(2, 1, color)};
            break;
        case 5: // S shape
            blocks = {Block(1, 0, color), Block(2, 0, color), Block(0, 1, color), Block(1, 1, color)};
            break;
        case 6: // Z shape
            blocks = {Block(0, 0, color), Block(1, 0, color), Block(1, 1, color), Block(2, 1, color)};
            break;
        case 7: // T shape
            blocks = {Block(1, 0, color), Block(0, 1, color), Block(1, 1, color), Block(2, 1, color)};
            break;
    }
}
