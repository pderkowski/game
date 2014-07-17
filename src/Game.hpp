/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Players.hpp"

class Game {
public:
    Game(int rows, int columns, int players);

    void start();

private:
    void restart();
    void quit();
    void toggleMenu();
    void handleEvents();
    void handleLeftClick(const sf::Event& event);
    void handleRightClick(const sf::Event& event);
    void handleMouseWheelMoved(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);
    void handleAPressed();
    void handleEnterPressed();

    std::shared_ptr<sf::RenderWindow> window_;
    Map map_;
    Menu menu_;
    Players players_;
};

#endif  // GAME_HPP_
