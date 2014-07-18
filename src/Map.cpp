/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"
#include "MapRenderer.hpp"

Map::Map(int rows, int columns, std::shared_ptr<sf::RenderTarget> target)
    : model_(std::make_shared<MapModel>(MapGenerator::generateMap(rows, columns))),
    renderer_(rows, columns, 96, 48, target),
    mapDrawer_(*model_, &renderer_),
    minimapDrawer_(model_, &renderer_)
{
    minimapDrawer_.updateMinimap(renderer_.getDisplayedRectangle());
}

void Map::draw() const {
    mapDrawer_.draw();
    minimapDrawer_.draw();
}

const MapRenderer* Map::getRenderer() const {
    return &renderer_;
}

void Map::generateMap() {
    *model_ = MapGenerator::generateMap(model_->getRowsNo(), model_->getColumnsNo());
    mapDrawer_.setModel(*model_);
    minimapDrawer_.setModel(model_);
    minimapDrawer_.updateMinimap(renderer_.getDisplayedRectangle());
}

// void Map::handleLeftClick(const sf::Event& e) {
//     selection_.clear();
//     selection_.setSource(mapDrawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));
//     mapDrawer_.updatePathLayer(std::vector<Tile>());
//     mapDrawer_.updateSelectionLayer(selection_);
// }

// void Map::handleRightClick(const sf::Event& e) {
//     std::vector<Tile> path;

//     if (selection_.isUnitSelected()) {
//         std::shared_ptr<Tile> destination
//             = mapDrawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

//         units::Unit* selectedUnit = selection_.getSelectedUnit();
//         Pathfinder pathfinder(selectedUnit->getMovingCosts());

//         auto source = selection_.getSource();
//         if (pathfinder.doesPathExist(*source, *destination)) {
//             path = pathfinder.findPath(*source, *destination);

//             if (selection_.isDestinationSelected() && *(selection_.getDestination()) == *destination) {
//                 for (size_t i = 0; i + 1 < path.size(); ++i) {
//                     auto direction = path[i].getDirection(path[i + 1]);
//                     moveUnit(direction);
//                 }

//                 path.clear();
//                 selection_.clear();
//                 selection_.setSource(destination);
//             } else {
//                 selection_.setDestination(destination);
//             }
//         }
//     }

//     mapDrawer_.updatePathLayer(path);
//     mapDrawer_.updateSelectionLayer(selection_);
// }

void Map::handleMouseWheelMoved(const sf::Event& event) {
    renderer_.zoomView(event.mouseWheel.delta,
        sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y));
    minimapDrawer_.updateMinimap(renderer_.getDisplayedRectangle());
}

void Map::handleMouseMoved(const sf::Event& event)  {
    renderer_.scrollView(calculateHorizontalShift(event.mouseMove.x),
        calculateVerticalShift(event.mouseMove.y));
    minimapDrawer_.updateMinimap(renderer_.getDisplayedRectangle());
}

int Map::calculateHorizontalShift(float mouseXPosition) const {
    const int scrollMarginSize = 20;

    if (mouseXPosition < scrollMarginSize) {
        return mouseXPosition - scrollMarginSize;
    } else if (mouseXPosition > renderer_.getSize().x - scrollMarginSize) {
        return scrollMarginSize - (renderer_.getSize().x - mouseXPosition);
    } else {
        return 0;
    }
}

int Map::calculateVerticalShift(float mouseYPosition) const {

    const int scrollMarginSize = 20;

    if (mouseYPosition < scrollMarginSize) {
        return mouseYPosition - scrollMarginSize;
    } else if (mouseYPosition > renderer_.getSize().y - scrollMarginSize) {
        return scrollMarginSize - (renderer_.getSize().y - mouseYPosition);
    } else {
        return 0;
    }
}

// void Map::moveUnit(tileenums::Direction direction) {
//     if (selection_.isUnitSelected()) {
//         units::Unit* unit = selection_.getSelectedUnit();
//         auto oldPosition = unit->getPosition();

//         mapDrawer_.updateUnitLayer(*unit, oldPosition, nullptr); // remove old drawing

//         if (unit->canMoveTo(direction))
//             unit->moveTo(direction);

//         auto newPosition = unit->getPosition();
//         selection_.setSource(std::const_pointer_cast<Tile>(newPosition));
//         mapDrawer_.updateUnitLayer(*unit, nullptr, newPosition);
//     }
// }

// void Map::handleAPressed() {
//     if (selection_.isSourceSelected()) {
//         model_->addUnit(units::Unit(selection_.getSource()->coords, units::Type::Phalanx, model_.get()));
//         units::Unit* unit = selection_.getSelectedUnit();
//         mapDrawer_.updateUnitLayer(*unit, nullptr, unit->getPosition());
//     }
// }

