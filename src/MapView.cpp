/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapView.hpp"

MapView::MapView(std::shared_ptr<Map> map, const std::map<Tile::Type, sf::Texture>& tileTextures)
    : map_(map), tileTextures_(tileTextures), offset_(0, 0), tileWidth_(16), tileHeight_(16)
{ }

void MapView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sprite.setTextureRect(sf::IntRect(0, 0, tileWidth_, tileHeight_));

    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    sprite.move(offset_);

    for (int r = 0; r < map_->getRowsNo(); ++r) {
        for (int c = 0; c < map_->getColumnsNo(); ++c) {
            if (map_->isVisible(r, c)) {
                Tile t = map_->getTile(r, c);
                sprite.setTexture(tileTextures_.at(t.getType()));
                target.draw(sprite, states);
            }

            sprite.move(xShift, 0);
        }
        sprite.move(-(map_->getColumnsNo() * xShift), yShift);
    }
}

void MapView::setOffset(const sf::Vector2f& offset) {
    offset_ = offset;
}

float MapView::width() const {
    return 2 * offset_.x + (map_->getColumnsNo() - 1) + map_->getColumnsNo() * tileWidth_;
}

float MapView::height() const {
    return 2 * offset_.y + (map_->getRowsNo() - 1) + map_->getRowsNo() * tileHeight_;
}

int MapView::convertXCoordsToColumnNo(int x) const {
    int column = floor((x - offset_.x) / (tileWidth_ + 1));

    if (column < 0 || column >= map_->getColumnsNo())
        return Map::OutOfBounds;
    else
        return column;
}

int MapView::convertYCoordsToRowNo(int y) const {
    int row = floor((y - offset_.y) / (tileHeight_ + 1));

    if (row < 0 || row >= map_->getRowsNo())
        return Map::OutOfBounds;
    else
        return row;
}
