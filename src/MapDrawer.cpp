/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include <algorithm>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Resources.hpp"
#include "Tile.hpp"

MapDrawer::MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target,
    Resources& resources)
        : model_(model),
        target_(target),
        mapView_(sf::FloatRect(0, 0, target->getSize().x, target->getSize().y)),
        tileTextures_{  // NOLINT
            { Tile::Type::Empty, resources.loadTexture("tiles/empty.png") },
            { Tile::Type::Water, resources.loadTexture("tiles/water.png") },
            { Tile::Type::Hills, resources.loadTexture("tiles/hills.png") },
            { Tile::Type::Plains, resources.loadTexture("tiles/plains.png") },
            { Tile::Type::Mountains, resources.loadTexture("tiles/mountains.png") }
        },
        tileSize_(16)
{
    target_->setView(mapView_);
}

void MapDrawer::draw() const {
    sf::Sprite sprite;
    sprite.setTextureRect(sf::IntRect(0, 0, tileSize_, tileSize_));

    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    for (int r = 0; r < model_->getRowsNo(); ++r) {
        for (int c = 0; c < model_->getColumnsNo(); ++c) {
            if (model_->getTile(r, c)->isVisible) {
                sprite.setTexture(tileTextures_.at(model_->getTile(r, c)->type));
                target_->draw(sprite);
            }

            sprite.move(xShift, 0);
        }
        sprite.move(-(model_->getColumnsNo() * xShift), yShift);
    }
}

std::shared_ptr<const sf::RenderTarget> MapDrawer::getTarget() const {
    return target_;
}

std::shared_ptr<Tile> MapDrawer::getObjectByPosition(const sf::Vector2i& position) {
    int column = mapXCoordsToColumn(target_->mapPixelToCoords(position).x);
    int row = mapYCoordsToRow(target_->mapPixelToCoords(position).y);

    if (column != MapModel::OutOfBounds && row != MapModel::OutOfBounds)
        return model_->getTile(row, column);
    else
        return std::shared_ptr<Tile>();
}

void MapDrawer::scrollView(float x, float y) {
    mapView_.move(boundShift(x, y));
    target_->setView(mapView_);
}

sf::Vector2f MapDrawer::boundShift(float x, float y) const {
    sf::Vector2f safeShift;

    sf::FloatRect bounds(0, 0, getMapWidth(tileSize_), getMapHeight(tileSize_));
    sf::FloatRect displayed(mapView_.getCenter().x - mapView_.getSize().x / 2,
        mapView_.getCenter().y - mapView_.getSize().y / 2,
        mapView_.getSize().x, mapView_.getSize().y);

    float maxLeftShiftPossible = bounds.left - displayed.left;
    float maxRightShiftPossible = bounds.left + bounds.width - displayed.left - displayed.width;
    float maxTopShiftPossible = bounds.top - displayed.top;
    float maxBottomShiftPossible = bounds.top + bounds.height - displayed.top - displayed.height;

    safeShift.x = (x < 0)? std::min(std::max(x, maxLeftShiftPossible), maxRightShiftPossible)
        : std::max(std::min(x, maxRightShiftPossible), maxLeftShiftPossible);
    safeShift.y = (y < 0)? std::min(std::max(y, maxTopShiftPossible), maxBottomShiftPossible)
        : std::max(std::min(y, maxBottomShiftPossible), maxTopShiftPossible);

    return safeShift;
}

void MapDrawer::zoomViem(int delta, const sf::Vector2i& mousePosition) {
    delta = delta / abs(delta);

    if (canZoom(delta)) {
        sf::Vector2f currentCoords = target_->mapPixelToCoords(mousePosition);
        sf::Vector2f newCoords = getCoordsAfterZoom(delta, mousePosition);

        tileSize_ += delta;

        scrollView(newCoords.x - currentCoords.x, newCoords.y - currentCoords.y);
    }
}

bool MapDrawer::canZoom(int delta) const {
    const int minTileSize = 4;
    const int maxTileSize = 32;

    int newTileSize = tileSize_ + delta;
    return newTileSize >= minTileSize
        && newTileSize <= maxTileSize
        && getMapWidth(newTileSize) >= target_->getSize().x
        && getMapHeight(newTileSize) >= target_->getSize().y;
}

sf::Vector2f MapDrawer::getCoordsAfterZoom(int delta, const sf::Vector2i& mousePosition) const {
    sf::Vector2f currentCoords = target_->mapPixelToCoords(mousePosition);
    double xPositionFraction = currentCoords.x / getMapWidth(tileSize_);
    double yPositionFraction = currentCoords.y / getMapHeight(tileSize_);
    return sf::Vector2f(xPositionFraction * getMapWidth(tileSize_ + delta),
        yPositionFraction * getMapHeight(tileSize_ + delta));
}

float MapDrawer::getMapWidth(int tileSize) const {
    return (model_->getColumnsNo() - 1) + model_->getColumnsNo() * tileSize;
}

float MapDrawer::getMapHeight(int tileSize) const {
    return (model_->getRowsNo() - 1) + model_->getRowsNo() * tileSize;
}

int MapDrawer::mapXCoordsToColumn(int x) const {
    int column = floor(x / (tileSize_ + 1));

    if (column < 0 || column >= model_->getColumnsNo())
        return MapModel::OutOfBounds;
    else
        return column;
}

int MapDrawer::mapYCoordsToRow(int y) const {
    int row = floor(y / (tileSize_ + 1));

    if (row < 0 || row >= model_->getRowsNo())
        return MapModel::OutOfBounds;
    else
        return row;
}

sf::IntRect MapDrawer::getDisplayedTilesRect() const {
    sf::Vector2i leftTop(0, 0);
    sf::Vector2i rightBottom(target_->getSize().x - 1, target_->getSize().y - 1);

    int left = mapXCoordsToColumn(target_->mapPixelToCoords(leftTop).x);
    int top = mapYCoordsToRow(target_->mapPixelToCoords(leftTop).y);
    int right = mapXCoordsToColumn(target_->mapPixelToCoords(rightBottom).x);
    int bottom = mapYCoordsToRow(target_->mapPixelToCoords(rightBottom).y);

    left = (left == MapModel::OutOfBounds)? 0 : left;
    top = (top == MapModel::OutOfBounds)? 0 : top;
    right = (right == MapModel::OutOfBounds)? (model_->getColumnsNo() - 1) : right;
    bottom = (bottom == MapModel::OutOfBounds)? (model_->getRowsNo() - 1) : bottom;

    return sf::IntRect(left, top, right - left, bottom - top);
}
