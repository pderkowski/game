/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"
#include "Renderer.hpp"

Map::Map(int rows, int columns, std::shared_ptr<sf::RenderTarget> target)
    : model_(std::make_shared<MapModel>(MapGenerator::generateMap(rows, columns))),
    renderer_(rows, columns, 96, 48, target),
    mapDrawer_(*model_, &renderer_)
{ }

void Map::draw() const {
    mapDrawer_.draw();
}

std::shared_ptr<const MapModel> Map::getModel() const {
    return model_;
}

const Renderer* Map::getRenderer() const {
    return &renderer_;
}

void Map::generateMap() {
    *model_ = MapGenerator::generateMap(model_->getRowsNo(), model_->getColumnsNo());
    mapDrawer_.setModel(*model_);
}

void Map::handleMouseWheelMoved(const sf::Event& event) {
    renderer_.zoomView(event.mouseWheel.delta,
        sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y));
}

sf::Vector2f Map::scrollView()  {
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    return renderer_.scrollView(calculateHorizontalShift(mousePosition.x) * 2,
        calculateVerticalShift(mousePosition.y) * 2);
}

int Map::calculateHorizontalShift(int mouseXPosition) const {
    const int scrollMarginSize = 50;

    if (mouseXPosition < scrollMarginSize) {
        return mouseXPosition - scrollMarginSize;
    } else if (mouseXPosition > static_cast<int>(renderer_.getSize().x) - scrollMarginSize) {
        return scrollMarginSize - (static_cast<int>(renderer_.getSize().x) - mouseXPosition);
    } else {
        return 0;
    }
}

int Map::calculateVerticalShift(int mouseYPosition) const {
    const int scrollMarginSize = 50;

    if (mouseYPosition < scrollMarginSize) {
        return mouseYPosition - scrollMarginSize;
    } else if (mouseYPosition > static_cast<int>(renderer_.getSize().y) - scrollMarginSize) {
        return scrollMarginSize - (static_cast<int>(renderer_.getSize().y) - mouseYPosition);
    } else {
        return 0;
    }
}
