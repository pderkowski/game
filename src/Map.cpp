/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <memory>
#include "boost/optional.hpp"
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Tile.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"

Map::Map(int rows, int columns, std::shared_ptr<sf::RenderWindow> target)
        : model_(std::make_shared<MapModel>(MapGenerator::generateMap(rows, columns))),
        mapDrawer_(model_, target),
        minimapDrawer_(model_, target)
{
    minimapDrawer_.updateMinimap(mapDrawer_.getDisplayedRectangle());
}

void Map::draw() const {
    mapDrawer_.draw();
    minimapDrawer_.draw();
}

void Map::generateMap() {
    *model_ = MapGenerator::generateMap(model_->getRowsNo(), model_->getColumnsNo());
    mapDrawer_.setModel(model_);
    minimapDrawer_.setModel(model_);
    minimapDrawer_.updateMinimap(mapDrawer_.getDisplayedRectangle());
}

void Map::handleLeftClick(const sf::Event& e) {
    selection_.setSource(mapDrawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));
}

void Map::handleRightClick(const sf::Event& e) {
    if (selection_.isUnitSelected()) {
        std::shared_ptr<Tile> destination
            = mapDrawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

        if (selection_.isDestinationSelected() && *(selection_.getDestination()) == *destination) {
            auto source = selection_.getSource();

            if (pathfinder_.doesPathExist(*source, *destination)) {
                std::vector<tileenums::Direction> steps = pathfinder_.findPath(*source, *destination);

                for (auto step : steps) {
                    moveUnit(step);
                }
            }

            selection_.clear();
            selection_.setSource(destination);
        } else {
            selection_.setDestination(destination);
        }
    }
}

void Map::handleMouseWheelMoved(const sf::Event& event) {
    mapDrawer_.zoomViem(event.mouseWheel.delta,
        sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y));
    minimapDrawer_.updateMinimap(mapDrawer_.getDisplayedRectangle());
}

void Map::handleMouseMoved(const sf::Event& event)  {
    mapDrawer_.scrollView(calculateHorizontalShift(event.mouseMove.x),
        calculateVerticalShift(event.mouseMove.y));
    minimapDrawer_.updateMinimap(mapDrawer_.getDisplayedRectangle());
}

int Map::calculateHorizontalShift(float mouseXPosition) const {
    const int scrollMarginSize = 20;

    if (mouseXPosition < scrollMarginSize) {
        return mouseXPosition - scrollMarginSize;
    } else if (mouseXPosition > mapDrawer_.getTarget()->getSize().x - scrollMarginSize) {
        return scrollMarginSize - (mapDrawer_.getTarget()->getSize().x - mouseXPosition);
    } else {
        return 0;
    }
}

int Map::calculateVerticalShift(float mouseYPosition) const {

    const int scrollMarginSize = 20;

    if (mouseYPosition < scrollMarginSize) {
        return mouseYPosition - scrollMarginSize;
    } else if (mouseYPosition > mapDrawer_.getTarget()->getSize().y - scrollMarginSize) {
        return scrollMarginSize - (mapDrawer_.getTarget()->getSize().y - mouseYPosition);
    } else {
        return 0;
    }
}

void Map::moveUnit(tileenums::Direction direction) {
    if (selection_.isUnitSelected()) {
        units::Unit* unit = selection_.getSelectedUnit();
        auto oldPosition = unit->getPosition();

        if (unit->canMoveTo(direction))
            unit->moveTo(direction);

        auto newPosition = unit->getPosition();
        selection_.setSource(std::const_pointer_cast<Tile>(newPosition));
        mapDrawer_.updateUnitLayer(*unit, oldPosition, newPosition);
    }
}
