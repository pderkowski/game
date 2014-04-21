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
        offset_(10, 10), tileSize_(16) {
    target_->setView(mapView_);
}

void MapDrawer::draw() const {
    sf::Sprite sprite;
    sprite.setTextureRect(sf::IntRect(0, 0, tileSize_, tileSize_));

    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    sprite.move(offset_);

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

std::shared_ptr<Tile> MapDrawer::getObjectByPosition(const sf::Vector2i& position) {
    int column = mapXCoordsToColumn(target_->mapPixelToCoords(position).x);
    int row = mapYCoordsToRow(target_->mapPixelToCoords(position).y);

    if (column != MapModel::OutOfBounds && row != MapModel::OutOfBounds)
        return model_->getTile(row, column);
    else
        return std::shared_ptr<Tile>();
}

void MapDrawer::scrollView(int x, int y) {
    mapView_.move(calculateHorizontalShift(x), calculateVerticalShift(y));
    target_->setView(mapView_);
}

void MapDrawer::zoomViemBy(int delta) {
    delta = delta / abs(delta);

    if (canZoomBy(delta))
        tileSize_ = tileSize_ + delta;
}

bool MapDrawer::canZoomBy(int delta) {
    const int minTileSize = 4;
    const int maxTileSize = 32;

    int newTileSize = tileSize_ + delta;
    return newTileSize >= minTileSize
        && newTileSize <= maxTileSize
        && getMapWidth(newTileSize) >= target_->getSize().x
        && getMapHeight(newTileSize) >= target_->getSize().y;
}

float MapDrawer::getMapWidth(int tileSize) const {
    return 2 * offset_.x + (model_->getColumnsNo() - 1) + model_->getColumnsNo() * tileSize;
}

float MapDrawer::getMapHeight(int tileSize) const {
    return 2 * offset_.y + (model_->getRowsNo() - 1) + model_->getRowsNo() * tileSize;
}

int MapDrawer::mapXCoordsToColumn(int x) const {
    int column = floor((x - offset_.x) / (tileSize_ + 1));

    if (column < 0 || column >= model_->getColumnsNo())
        return MapModel::OutOfBounds;
    else
        return column;
}

int MapDrawer::mapYCoordsToRow(int y) const {
    int row = floor((y - offset_.y) / (tileSize_ + 1));

    if (row < 0 || row >= model_->getRowsNo())
        return MapModel::OutOfBounds;
    else
        return row;
}

float MapDrawer::calculateHorizontalShift(float mouseXPosition) const {
    if (mouseXPosition < scrollMarginSize_) {
        return std::max(mouseXPosition - scrollMarginSize_,
            -(mapView_.getCenter().x - mapView_.getSize().x / 2));
    } else if (mouseXPosition > target_->getSize().x - scrollMarginSize_) {
        return std::min(scrollMarginSize_ - (target_->getSize().x - mouseXPosition),
            getMapWidth(tileSize_) - (mapView_.getCenter().x + mapView_.getSize().x / 2));
    } else {
        return 0;
    }
}

float MapDrawer::calculateVerticalShift(float mouseYPosition) const {
    if (mouseYPosition < scrollMarginSize_) {
        return std::max(mouseYPosition - scrollMarginSize_,
            -(mapView_.getCenter().y - mapView_.getSize().y / 2));
    } else if (mouseYPosition > target_->getSize().y - scrollMarginSize_) {
        return std::min(scrollMarginSize_ - (target_->getSize().y - mouseYPosition),
            getMapHeight(tileSize_) - (mapView_.getCenter().y + mapView_.getSize().y / 2));
    } else {
        return 0;
    }
}

sf::IntRect MapDrawer::getDisplayedTilesRect() const {
    sf::Vector2i leftTop(offset_.x + 1, offset_.y + 1);
    sf::Vector2i rightBottom(target_->getSize().x - offset_.x - 1,
        target_->getSize().y - offset_.y - 1);

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
