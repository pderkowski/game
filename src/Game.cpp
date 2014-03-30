/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "Game.hpp"

Game::Game(const std::string& name, const Grid& board)
    : board_(board), window_(sf::VideoMode(board.width(), board.height()), name)
{ }

void Game::start() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        window_.clear();
        window_.draw(board_);
        window_.display();
    }
}
