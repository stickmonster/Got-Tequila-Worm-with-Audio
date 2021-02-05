#include "renderer.h"
#include <iostream>
#include <string>


Mix_Chunk* gArriba = NULL;
Mix_Chunk* gMuerte = NULL;
Mix_Chunk* gTequila = NULL;

Renderer::Renderer(const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
    screen_height(screen_height),
    grid_width(grid_width),
    grid_height(grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    //Initialise PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError());
        //success = false;

    }

    //Initialise SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialise! SDL_mixer Error: %s\n", Mix_GetError());
        //success = false;
    }
        
 
    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, screen_width,
        screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load sound effects
    gArriba = Mix_LoadWAV("mediumArriba.wav");
    if (gArriba == NULL)
    {
        printf("Failed to load Arriba sound effect!");
        success = false;
    }

    gMuerte = Mix_LoadWAV("esMuerte.wav");
    if (gMuerte == NULL)
    {
        printf("Failed to load Muerte sound effect!");
        success = false;
    }

    gTequila = Mix_LoadWAV("Tequila.wav");
    if (gTequila == NULL)
    {
        printf("Failed to load Tequila sound effect!");
        success = false;
    }


    return success;
}


Renderer::~Renderer() {
    Mix_FreeChunk(gArriba);
    gArriba = NULL;
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}




void Renderer::Render(Snake const snake, std::vector<Snake> const worms, SDL_Point const& food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render food
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);


    RenderSnake(snake);
    for (Snake comSnake : worms) {
        RenderSnake(comSnake);
    }
    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderSnake(Snake const snake) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;
    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const& point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.is_bot) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x71, 0x00, 0xD1, 0xFF);
    }
    else if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    }
    else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);
}



void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{ "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) };
    SDL_SetWindowTitle(sdl_window, title.c_str());
}