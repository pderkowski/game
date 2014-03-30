/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "SFML/Graphics.hpp"
#include "Grid.hpp"

class Game {
public:
    Game(const std::string& name, const Grid& board);

    void start();

private:
    Grid board_;
    sf::RenderWindow window_;
};

#endif  // GRID_H_
