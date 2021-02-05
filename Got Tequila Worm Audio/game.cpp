#include "game.h"
#include <iostream>
#include "SDL.h"
#include <SDL_mixer.h>
#include <chrono>
#include <algorithm>



Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
    engine(dev()),
    random_w(0, static_cast<int>(grid_width - 3)),
    random_h(0, static_cast<int>(grid_height - 5)) {
    PlaceFood();
    Mix_Chunk* gTequila = Mix_LoadWAV("Tequila.wav");
    Mix_PlayChannel(-1, gTequila, 0);
}

void Game::addSnake(std::size_t grid_width, std::size_t grid_height) {
    Snake new_snake = Snake(grid_width, grid_height);
    new_snake.is_bot = true;
    computer_worms.push_back(new_snake);
 }

void Game::Run(Controller const& controller, Renderer& renderer,
    std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();


        // Input, Update, Render - the main game loop.
       // controller.HandleInput(running, snake);
        Update();
        renderer.Render(snake, computer_worms, food);

        frame_end = SDL_GetTicks();

        controller.HandleInput_human(running, snake);
        for (Snake& comSnake : computer_worms) {
            controller.HandleInput_computer(comSnake, &food);
        }

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }

}


void Game::Update() {
    if (!snake.alive) 
    {
        Mix_Chunk* gMuerte = Mix_LoadWAV("esMuerte.wav");
        Mix_PlayChannel(-1, gMuerte, 0);
        
        return;    
    }

    snake.Update();
    for (Snake& comSnake : computer_worms) {
        comSnake.Update();
    }

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        // score++;
        Mix_Chunk* gArriba = Mix_LoadWAV("mediumArriba.wav");
        Mix_PlayChannel(-1, gArriba, 0);
        Game::addSnake(new_x + 50, new_y + 50);
        PlaceFood();
        // Grow snake and increase speed.
        snake.ShrinkBody();
        snake.speed += 0.02;
        
    }
}

int Game::GetSize() const { return snake.size; }