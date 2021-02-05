#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const& controller, Renderer& renderer,
        std::size_t target_frame_duration);
    int GetSize() const;
    void addSnake(std::size_t grid_width, std::size_t grid_height);

private:
    Snake snake;
    SDL_Point food;
    std::vector<Snake> computer_worms;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int score{};

    void PlaceFood();
    void Update();

};

#endif