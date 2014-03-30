/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "Game.hpp"

Game::Game(const std::string& name, std::shared_ptr<Board> board, const BoardView& boardView)
    : board_(board),
    boardView_(boardView),
    window_(sf::VideoMode(boardView.width(), boardView.height()), name)
{ }

void Game::start() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        window_.clear();
        window_.draw(boardView_);
        window_.display();
    }
}
