#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "snake.h"

class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
        const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(Snake const snake, std::vector<Snake> const worms, SDL_Point const& food);
    void RenderSnake(Snake const snake);

    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif
