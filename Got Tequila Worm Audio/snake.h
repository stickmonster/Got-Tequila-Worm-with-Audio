#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>


class Snake {
public:
    enum class Direction { kUp, kDown, kLeft, kRight };

    Snake(int grid_width, int grid_height)
        : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

    void Update();

    void ShrinkBody();
    bool SnakeCell(int x, int y);
    int GetGridWidth();
    int GetGridHeight();


    Direction direction = Direction::kUp;

    float speed{ 0.1f };
    int size{ 1 };
    bool alive{ true };
    bool is_bot{ false };
    float head_x;
    float head_y;
    std::vector<SDL_Point> body{ 7 };

private:
    void UpdateHead();
    void UpdateBody(SDL_Point& current_cell, SDL_Point& prev_cell);

    bool winning{ false };
    int grid_width;
    int grid_height;
};

#endif
