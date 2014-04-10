/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <algorithm>
#include <string>
#include "MapView.hpp"
#include "MapGenerator.hpp"
#include "Game.hpp"

Game::Game(const std::string& name, std::shared_ptr<Map> map, const MapView& mapView)
        : map_(map),
        mapView_(mapView),
        window_(
            sf::VideoMode::getFullscreenModes()[0],
            name,
            sf::Style::Fullscreen),
        view_(sf::FloatRect(0, 0, window_.getSize().x, window_.getSize().y)) {
    window_.setView(view_);
}

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

    int column = mapView_.convertXCoordsToColumnNo(window_.mapPixelToCoords(mousePosition).x);
    int row = mapView_.convertYCoordsToRowNo(window_.mapPixelToCoords(mousePosition).y);

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
            -(view_.getCenter().x - view_.getSize().x / 2));
        view_.move(shift, 0);
        window_.setView(view_);
    } else if (event.mouseMove.x > static_cast<int>(window_.getSize().x) - scrollAreaSize) {
        float shift = std::min(
            static_cast<float>(scrollAreaSize - (window_.getSize().x - event.mouseMove.x)),
            mapView_.width() - (view_.getCenter().x + view_.getSize().x / 2));
        view_.move(shift, 0);
        window_.setView(view_);
    }

    if (event.mouseMove.y < scrollAreaSize) {
        float shift = std::max(static_cast<float>(event.mouseMove.y - scrollAreaSize),
            -(view_.getCenter().y - view_.getSize().y / 2));
        view_.move(0, shift);
        window_.setView(view_);
    } else if (event.mouseMove.y > static_cast<int>(window_.getSize().y) - scrollAreaSize) {
        float shift = std::min(
            static_cast<float>(scrollAreaSize - (window_.getSize().y - event.mouseMove.y)),
            mapView_.height() - (view_.getCenter().y + view_.getSize().y / 2));
        view_.move(0, shift);
        window_.setView(view_);
    }
}
