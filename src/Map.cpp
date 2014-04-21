/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Tile.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"

Map::Map(int rows, int columns, std::shared_ptr<sf::RenderWindow> target, Resources& resources)
        : model_(std::make_shared<MapModel>(MapGenerator::generateMap(rows, columns))),
        mapDrawer_(model_, target, resources),
        minimapDrawer_(model_, target, resources) {
    minimapDrawer_.updateView(mapDrawer_.getDisplayedTilesRect());
}

void Map::draw() const {
    mapDrawer_.draw();
    minimapDrawer_.draw();
}

void Map::generateMap() {
    *model_ = MapGenerator::generateMap(model_->getRowsNo(), model_->getColumnsNo());
    minimapDrawer_.createMinimap();
    minimapDrawer_.updateView(mapDrawer_.getDisplayedTilesRect());
}

void Map::handleClick(const sf::Event& e) {
    std::shared_ptr<Tile> clickedObject
        = mapDrawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

    if (clickedObject) {
        clickedObject->toggleVisibility();
    }
}

void Map::handleMouseWheelMoved(const sf::Event& event) {
    mapDrawer_.zoomViem(event.mouseWheel.delta,
        sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y));
    minimapDrawer_.updateView(mapDrawer_.getDisplayedTilesRect());
}

void Map::handleMouseMoved(const sf::Event& event)  {
    mapDrawer_.scrollView(calculateHorizontalShift(event.mouseMove.x),
        calculateVerticalShift(event.mouseMove.y));
    minimapDrawer_.updateView(mapDrawer_.getDisplayedTilesRect());
}

float Map::calculateHorizontalShift(float mouseXPosition) const {
    const int scrollMarginSize = 20;

    if (mouseXPosition < scrollMarginSize) {
        return mouseXPosition - scrollMarginSize;
    } else if (mouseXPosition > mapDrawer_.getTarget()->getSize().x - scrollMarginSize) {
        return scrollMarginSize - (mapDrawer_.getTarget()->getSize().x - mouseXPosition);
    } else {
        return 0;
    }
}

float Map::calculateVerticalShift(float mouseYPosition) const {
    const int scrollMarginSize = 20;

    if (mouseYPosition < scrollMarginSize) {
        return mouseYPosition - scrollMarginSize;
    } else if (mouseYPosition > mapDrawer_.getTarget()->getSize().y - scrollMarginSize) {
        return scrollMarginSize - (mapDrawer_.getTarget()->getSize().y - mouseYPosition);
    } else {
        return 0;
    }
}
