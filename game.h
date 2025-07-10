#pragma once
#include <bits/stdc++.h>
class GameOfLife {
public:
    GameOfLife(int width, int height);
    void update();
    void toggleCell(int x, int y);
    void clear();

    const std::vector<std::vector<bool>>& getGrid() const;
    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> buffer;

    int countNeighbors(int x, int y) const;
};