/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "SFML/Graphics.hpp"
#include "BoardView.hpp"

class Game {
public:
    Game(const std::string& name, const BoardView& boardView);

    void start();

private:
    BoardView boardView_;
    sf::RenderWindow window_;
};

#endif  // GAME_H_
