#include "Board.hpp"

Board::Board(int width, int height)
    : width(width), height(height), grid(height, std::vector<chtype>(width, 0)) {}

bool Board::collidesWith(const Tetrimino& tetrimino) const {
    for (const auto& block : tetrimino.getBlocks()) {
        int x = block.getX() + tetrimino.getX();
        int y = block.getY() + tetrimino.getY();
        if (x < 0 || x >= width || y < 0 || y >= height || grid[y][x] != 0) {
            return true;
        }
    }
    if (tetrimino.getBlocks().size() == 0){
        return true;
    }
    return false;
}

void Board::merge(const Tetrimino& tetrimino) {
    for (const auto& block : tetrimino.getBlocks()) {

        int x = block.getX() + tetrimino.getX();
        int y = block.getY() + tetrimino.getY();
        if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
            grid[y][x] = block.getColor();
        }
    }
}

int Board::clearLines() {
    int linesCleared = 0;
    for (int y = 0; y < height; ++y) {
        bool full = true;
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == 0) {
                full = false;
                break;
            }
        }
        if (full) {
            grid.erase(grid.begin() + y);
            grid.insert(grid.begin(), std::vector<chtype>(width, 0));
            ++linesCleared;
        }
    }
    return linesCleared;
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

void Board::draw(WINDOW* win) const {
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            int color = grid[y][x];
            if (color != 0) {
                Tetrimino::drawBlock(win, x, y, color);
            } else {
                mvwaddch(win, y, x, ' ');
            }
        }
    }
}


