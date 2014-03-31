/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "MapView.hpp"

class Game {
public:
    Game(const std::string& name, std::shared_ptr<Map> map, const MapView& mapView);

    void start();

private:
    void handleLeftClick(const sf::Event& event);

    std::shared_ptr<Map> map_;
    MapView mapView_;
    sf::RenderWindow window_;
};

#endif  // GAME_H_
