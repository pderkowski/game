/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "MapView.hpp"

class Game {
public:
    Game(const std::string& name, std::shared_ptr<Map> map, const MapView& mapView);

    void start();

private:
    void handleEvents();
    void handleLeftClick(const sf::Event& event);
    void handleSpacePressed(const sf::Event& event);

    std::shared_ptr<Map> map_;
    MapView mapView_;
    sf::RenderWindow window_;
};

#endif  // GAME_HPP_
