/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <algorithm>
#include <string>
#include "MapDrawer.hpp"
#include "MapGenerator.hpp"
#include "Game.hpp"

Game::Game(const std::string& name, std::shared_ptr<Map> map, const MapDrawer& mapDrawer)
    : map_(map),
    mapDrawer_(mapDrawer),
    window_(
        sf::VideoMode::getFullscreenModes()[0],
        name,
        sf::Style::Fullscreen),
    mapView_(sf::FloatRect(0, 0, window_.getSize().x, window_.getSize().y))
{ }

void Game::start() {
    while (window_.isOpen()) {
        handleEvents();

        window_.clear();
        drawMap();
        window_.display();
    }
}

void Game::drawMap() {
    window_.setView(mapView_);
    window_.draw(mapDrawer_);
}

void Game::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        } else if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == sf::Mouse::Button::Left) {
            handleLeftClick(event);
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Space) {
                handleSpacePressed();
            } else if (event.key.code == sf::Keyboard::Key::Escape) {
                handleEscapePressed();
            }
        } else if (event.type == sf::Event::MouseMoved) {
            handleMouseMoved(event);
        }
    }
}

void Game::handleLeftClick(const sf::Event& event) {
    sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

    int column = mapDrawer_.convertXCoordsToColumnNo(window_.mapPixelToCoords(mousePosition).x);
    int row = mapDrawer_.convertYCoordsToRowNo(window_.mapPixelToCoords(mousePosition).y);

    if (column != Map::OutOfBounds && row != Map::OutOfBounds)
        map_->toggleVisibility(row, column);
}

void Game::handleSpacePressed() {
    *map_ = MapGenerator::generateMap(map_->getRowsNo(), map_->getColumnsNo());
}

void Game::handleEscapePressed() {
    exit(EXIT_SUCCESS);
}

void Game::handleMouseMoved(const sf::Event& event) {
    const int scrollAreaSize = 20;

    if (event.mouseMove.x < scrollAreaSize) {
        float shift = std::max(static_cast<float>(event.mouseMove.x - scrollAreaSize),
            -(mapView_.getCenter().x - mapView_.getSize().x / 2));
        mapView_.move(shift, 0);
    } else if (event.mouseMove.x > static_cast<int>(window_.getSize().x) - scrollAreaSize) {
        float shift = std::min(
            static_cast<float>(scrollAreaSize - (window_.getSize().x - event.mouseMove.x)),
            mapDrawer_.width() - (mapView_.getCenter().x + mapView_.getSize().x / 2));
        mapView_.move(shift, 0);
    }

    if (event.mouseMove.y < scrollAreaSize) {
        float shift = std::max(static_cast<float>(event.mouseMove.y - scrollAreaSize),
            -(mapView_.getCenter().y - mapView_.getSize().y / 2));
        mapView_.move(0, shift);
    } else if (event.mouseMove.y > static_cast<int>(window_.getSize().y) - scrollAreaSize) {
        float shift = std::min(
            static_cast<float>(scrollAreaSize - (window_.getSize().y - event.mouseMove.y)),
            mapDrawer_.height() - (mapView_.getCenter().y + mapView_.getSize().y / 2));
        mapView_.move(0, shift);
    }
}
