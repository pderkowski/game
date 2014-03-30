/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "SFML/Graphics.hpp"
#include "Board.hpp"
#include "BoardView.hpp"

class Game {
public:
    Game(const std::string& name, std::shared_ptr<Board> board, const BoardView& boardView);

    void start();

private:
    void handleLeftClick(const sf::Event& event);

    std::shared_ptr<Board> board_;
    BoardView boardView_;
    sf::RenderWindow window_;
};

#endif  // GAME_H_
