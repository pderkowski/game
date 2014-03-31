/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "Game.hpp"

Game::Game(const std::string& name, std::shared_ptr<Board> board, const BoardView& boardView)
    : board_(board),
    boardView_(boardView),
    window_(
        sf::VideoMode(boardView.width(), boardView.height()),
        name,
        sf::Style::Titlebar | sf::Style::Close)
{ }

void Game::start() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
            } else if (event.type == sf::Event::MouseButtonPressed
                    && event.mouseButton.button ==  sf::Mouse::Button::Left) {
                handleLeftClick(event);
            }
        }

        window_.clear();
        window_.draw(boardView_);
        window_.display();
    }
}

void Game::handleLeftClick(const sf::Event& event) {
    int column = boardView_.convertXCoordsToColumnNo(event.mouseButton.x);
    int row = boardView_.convertYCoordsToRowNo(event.mouseButton.y);

    if (column != Board::OutOfBounds && row != Board::OutOfBounds)
        board_->toggleVisibility(row, column);
}
