#define SDL_MAIN_HANDLED
#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <chrono>


int main() {
    SDL_SetMainReady();
    constexpr std::size_t kFramesPerSecond{ 60 };
    constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
    constexpr std::size_t kScreenWidth{ 640 };
    constexpr std::size_t kScreenHeight{ 640 };
    constexpr std::size_t kGridWidth{ 32 };
    constexpr std::size_t kGridHeight{ 32 };

   
    
    
    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;

    Game game(kGridWidth, kGridHeight);

    //Begin measuring time for the final score
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    game.Run(controller, renderer, kMsPerFrame);

    

    std::cout << "Gracias, you Got Tequila Worm! Es Muerte!\n";

    //end time point for time measurement
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto score_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Score: " << score_time / 1000000 << " segundos!\n";

    return 0;
}