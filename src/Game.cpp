/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <memory>
#include "Map.hpp"
#include "MapDrawer.hpp"
#include "MapGenerator.hpp"
#include "Menu.hpp"
#include "Game.hpp"

Game::Game(const std::string& name, int rows, int columns, Resources& resources)
        : map_(std::make_shared<Map>(MapGenerator::generateMap(rows, columns))),
        mapDrawer_(map_, resources),
        menu_(resources),
        window_(
            sf::VideoMode::getFullscreenModes()[0],
            name,
            sf::Style::Fullscreen),
        mapView_(sf::FloatRect(0, 0, window_.getSize().x, window_.getSize().y)) {
    mapDrawer_.setOffset(sf::Vector2f(10, 10));

    menu_.addItem("Return", [&] () { toggleMenu(); }); // NOLINT
    menu_.addItem("New game", [&] () { restart(); }); // NOLINT
    menu_.addItem("Quit game", [&] () { quit(); }); // NOLINT
}

void Game::start() {
    while (window_.isOpen()) {
        handleEvents();

        window_.clear();
        drawMap();
        drawMenuIfVisible();
        window_.display();
    }
}

void Game::drawMap() {
    window_.setView(mapView_);
    window_.draw(mapDrawer_);
}

void Game::drawMenuIfVisible() {
    if (menu_.isVisible()) {
        window_.draw(menu_);
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
            switch (event.key.code) {
            case sf::Keyboard::Key::Space:
                restart();
                break;
            case sf::Keyboard::Key::Escape:
                quit();
                break;
            case sf::Keyboard::Key::M:
                toggleMenu();
                break;
            default:
                break;
            }
        } else if (event.type == sf::Event::MouseWheelMoved) {
            handleMouseWheelMoved(event);
        } else if (event.type == sf::Event::MouseMoved) {
            handleMouseMoved(event);
        }
    }
}

void Game::handleLeftClick(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleClick(event, window_);
    } else {
       sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

       int column = mapDrawer_.convertXCoordsToColumnNo(window_.mapPixelToCoords(mousePosition).x);
       int row = mapDrawer_.convertYCoordsToRowNo(window_.mapPixelToCoords(mousePosition).y);

       if (column != Map::OutOfBounds && row != Map::OutOfBounds)
           map_->toggleVisibility(row, column);
   }
}

void Game::restart() {
    *map_ = MapGenerator::generateMap(map_->getRowsNo(), map_->getColumnsNo());
}

void Game::quit() {
    exit(EXIT_SUCCESS);
}

void Game::toggleMenu() {
    menu_.toggleVisibility();
}

void Game::handleMouseWheelMoved(const sf::Event& event) {
    const int minTileSize = 4;
    const int maxTileSize = 32;

    int newTileWidth = mapDrawer_.getTileWidth() + event.mouseWheel.delta;
    newTileWidth = std::min(newTileWidth, maxTileSize);
    newTileWidth = std::max(newTileWidth, minTileSize);
    mapDrawer_.setTileWidth(newTileWidth);

    int newTileHeight = mapDrawer_.getTileHeight() + event.mouseWheel.delta;
    newTileHeight = std::min(newTileHeight, maxTileSize);
    newTileHeight = std::max(newTileHeight, minTileSize);
    mapDrawer_.setTileHeight(newTileHeight);
}

void Game::handleMouseMoved(const sf::Event& event) {
    const int scrollMarginSize = 20;

    mapView_.move(calculateHorizontalShift(event.mouseMove.x, scrollMarginSize),
        calculateVerticalShift(event.mouseMove.y, scrollMarginSize));
}

float Game::calculateHorizontalShift(float mouseXPosition, float scrollMarginSize) const {
    if (mouseXPosition < scrollMarginSize) {
        return std::max(mouseXPosition - scrollMarginSize,
            -(mapView_.getCenter().x - mapView_.getSize().x / 2));
    } else if (mouseXPosition > window_.getSize().x - scrollMarginSize) {
        return std::min(scrollMarginSize - (window_.getSize().x - mouseXPosition),
            mapDrawer_.getMapWidth() - (mapView_.getCenter().x + mapView_.getSize().x / 2));
    } else {
        return 0;
    }
}

float Game::calculateVerticalShift(float mouseYPosition, float scrollMarginSize) const {
    if (mouseYPosition < scrollMarginSize) {
        return std::max(mouseYPosition - scrollMarginSize,
            -(mapView_.getCenter().y - mapView_.getSize().y / 2));
    } else if (mouseYPosition > window_.getSize().y - scrollMarginSize) {
        return std::min(scrollMarginSize - (window_.getSize().y - mouseYPosition),
            mapDrawer_.getMapHeight() - (mapView_.getCenter().y + mapView_.getSize().y / 2));
    } else {
        return 0;
    }
}
