/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "Menu.hpp"

class Game {
public:
    Game(int rows, int columns);

    void start();

private:
    void restart();
    void quit();
    void toggleMenu();
    void handleEvents();
    void handleClick(const sf::Event& event);
    void handleMouseWheelMoved(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);

    std::shared_ptr<sf::RenderWindow> window_;
    Map map_;
    Menu menu_;
};

#endif  // GAME_HPP_
