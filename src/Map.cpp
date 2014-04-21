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
    mapDrawer_.zoomViemBy(event.mouseWheel.delta);
    minimapDrawer_.updateView(mapDrawer_.getDisplayedTilesRect());
}

void Map::handleMouseMoved(const sf::Event& event)  {
    mapDrawer_.scrollView(event.mouseMove.x, event.mouseMove.y);
    minimapDrawer_.updateView(mapDrawer_.getDisplayedTilesRect());
}
