#include <SDL2/SDL.h>
#include "game.h"
#include <bits/stdc++.h>

const int CELL_SIZE = 10;
int WIDTH = 80, HEIGHT = 60, SPEED = 10;

int main(int argc, char* argv[]) {
    // Àðãóìåíòû çàïóñêà: --width=100 --height=100 --speed=10
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("--width=", 0) == 0) WIDTH = std::stoi(arg.substr(8));
        if (arg.rfind("--height=", 0) == 0) HEIGHT = std::stoi(arg.substr(9));
        if (arg.rfind("--speed=", 0) == 0) SPEED = std::stoi(arg.substr(8));
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Game of Life", 100, 100, WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    GameOfLife game(WIDTH, HEIGHT);
    bool running = true, paused = true;
    Uint32 lastUpdate = SDL_GetTicks();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) paused = !paused;
                if (e.key.keysym.sym == SDLK_c) game.clear();
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                game.toggleCell(x / CELL_SIZE, y / CELL_SIZE);
            }
        }

        if (!paused && SDL_GetTicks() - lastUpdate > 1000 / SPEED) {
            game.update();
            lastUpdate = SDL_GetTicks();
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        const auto& grid = game.getGrid();
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (grid[y][x]) {
                    SDL_Rect cell = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                    SDL_RenderFillRect(ren, &cell);
                }
            }
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
