#ifndef BLOCK_HPP
#define BLOCK_HPP

class Block {
public:
    Block(int x, int y, int color) : x(x), y(y), color(color) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getColor() const { return color; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setColor(int newColor) { color = newColor; }

private:
    int x;
    int y;
    int color;
};

#endif // BLOCK_HPP
