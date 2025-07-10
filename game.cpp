#include "game.h"

GameOfLife::GameOfLife(int w, int h) : width(w), height(h), grid(h, std::vector<bool>(w)), buffer(h, std::vector<bool>(w)) {}

void GameOfLife::update() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int neighbors = countNeighbors(x, y);
            if (grid[y][x]) {
                buffer[y][x] = (neighbors == 2 || neighbors == 3);
            }
            else {
                buffer[y][x] = (neighbors == 3);
            }
        }
    }
    grid.swap(buffer);
}

void GameOfLife::toggleCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height)
        grid[y][x] = !grid[y][x];
}

void GameOfLife::clear() {
    for (auto& row : grid) std::fill(row.begin(), row.end(), false);
}

int GameOfLife::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < width && ny < height && grid[ny][nx])
                ++count;
        }
    }
    return count;
}

const std::vector<std::vector<bool>>& GameOfLife::getGrid() const { return grid; }
int GameOfLife::getWidth() const { return width; }
int GameOfLife::getHeight() const { return height; }
