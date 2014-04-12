/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "MapDrawer.hpp"

class Game {
public:
    Game(const std::string& name, std::shared_ptr<Map> map, const MapDrawer& mapDrawer);

    void start();

private:
    void drawMap();

    void handleEvents();
    void handleLeftClick(const sf::Event& event);
    void handleSpacePressed();
    void handleEscapePressed();
    void handleMouseMoved(const sf::Event& event);

    std::shared_ptr<Map> map_;
    MapDrawer mapDrawer_;
    sf::RenderWindow window_;
    sf::View mapView_;
};

#endif  // GAME_HPP_
