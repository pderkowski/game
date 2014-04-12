/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "MapDrawer.hpp"

class Game {
public:
    Game(const std::string& name, int rows, int columns, Resources& resources);

    void start();

private:
    void drawMap();
    void drawMenuIfVisible();

    void handleEvents();
    void handleLeftClick(const sf::Event& event);
    void handleSpacePressed();
    void handleEscapePressed();
    void handleMPressed();
    void handleMouseWheelMoved(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);

    float calculateHorizontalShift(float mouseXPosition, float scrollMarginSize) const;
    float calculateVerticalShift(float mouseYPosition, float scrollMarginSize) const;

    std::shared_ptr<Map> map_;
    MapDrawer mapDrawer_;
    std::shared_ptr<Menu> menu_;
    MenuDrawer menuDrawer_;
    sf::RenderWindow window_;
    sf::View mapView_;
};

#endif  // GAME_HPP_
