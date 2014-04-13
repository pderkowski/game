/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapDrawer.hpp"
#include "Resources.hpp"
#include "Tile.hpp"

MapDrawer::MapDrawer(std::shared_ptr<Map> map, Resources& resources)
    : map_(map),
    tileTextures_{  // NOLINT
        { Tile::Type::Empty, resources.loadTexture("tiles/empty.png") },
        { Tile::Type::Water, resources.loadTexture("tiles/water.png") },
        { Tile::Type::Hills, resources.loadTexture("tiles/hills.png") },
        { Tile::Type::Plains, resources.loadTexture("tiles/plains.png") },
        { Tile::Type::Mountains, resources.loadTexture("tiles/mountains.png") }
    },
    offset_(0, 0), tileWidth_(16), tileHeight_(16)
{ }

void MapDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setTextureRect(sf::IntRect(0, 0, tileWidth_, tileHeight_));

    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    sprite.move(offset_);

    for (int r = 0; r < map_->getRowsNo(); ++r) {
        for (int c = 0; c < map_->getColumnsNo(); ++c) {
            if (map_->isVisible(r, c)) {
                sprite.setTexture(tileTextures_.at(map_->tile(r, c).getType()));
                target.draw(sprite, states);
            }

            sprite.move(xShift, 0);
        }
        sprite.move(-(map_->getColumnsNo() * xShift), yShift);
    }
}

int MapDrawer::getTileWidth() const {
    return tileWidth_;
}

int MapDrawer::getTileHeight() const {
    return tileHeight_;
}

float MapDrawer::getMapWidth() const {
    return 2 * offset_.x + (map_->getColumnsNo() - 1) + map_->getColumnsNo() * tileWidth_;
}

float MapDrawer::getMapHeight() const {
    return 2 * offset_.y + (map_->getRowsNo() - 1) + map_->getRowsNo() * tileHeight_;
}

void MapDrawer::setOffset(const sf::Vector2f& offset) {
    offset_ = offset;
}

void MapDrawer::setTileWidth(int tileWidth) {
    tileWidth_ = tileWidth;
}

void MapDrawer::setTileHeight(int tileHeight) {
    tileHeight_ = tileHeight;
}

int MapDrawer::convertXCoordsToColumnNo(int x) const {
    int column = floor((x - offset_.x) / (tileWidth_ + 1));

    if (column < 0 || column >= map_->getColumnsNo())
        return Map::OutOfBounds;
    else
        return column;
}

int MapDrawer::convertYCoordsToRowNo(int y) const {
    int row = floor((y - offset_.y) / (tileHeight_ + 1));

    if (row < 0 || row >= map_->getRowsNo())
        return Map::OutOfBounds;
    else
        return row;
}