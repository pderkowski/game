/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "MapView.hpp"
#include "MapGenerator.hpp"
#include "Game.hpp"

Game::Game(const std::string& name, std::shared_ptr<Map> map, const MapView& mapView)
    : map_(map),
    mapView_(mapView),
    window_(
        sf::VideoMode(mapView.width(), mapView.height()),
        name,
        sf::Style::Titlebar | sf::Style::Close)
{ }

void Game::start() {
    while (window_.isOpen()) {
        handleEvents();

        window_.clear();
        window_.draw(mapView_);
        window_.display();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        } else if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == sf::Mouse::Button::Left) {
            handleLeftClick(event);
        } else if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Key::Space) {
            handleSpacePressed(event);
        }
    }
}

void Game::handleLeftClick(const sf::Event& event) {
    int column = mapView_.convertXCoordsToColumnNo(event.mouseButton.x);
    int row = mapView_.convertYCoordsToRowNo(event.mouseButton.y);

    if (column != Map::OutOfBounds && row != Map::OutOfBounds)
        map_->toggleVisibility(row, column);
}

void Game::handleSpacePressed(__attribute__((unused)) const sf::Event& event) {
    *map_ = MapGenerator::generateMap(map_->getRowsNo(), map_->getColumnsNo());
}
