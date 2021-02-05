#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

enum Direction { COMPUTER_UP, COMPUTER_DOWN, COMPUTER_LEFT, COMPUTER_RIGHT };

class Controller {
public:
    void HandleInput(Snake& snake, int dir) const;
    void HandleInput_computer(Snake& snake, SDL_Point* const food) const;
    void HandleInput_human(bool& running, Snake& snake) const;

private:
    void ChangeDirection(Snake& snake, Snake::Direction input,
        Snake::Direction opposite) const;
    Direction ComputerMove(Snake& snake, SDL_Point* const food) const;
};

#endif
