/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include "SFML/Graphics.hpp"
#include "MapView.hpp"

MapView::MapView(std::shared_ptr<Map> map, const sf::Sprite& cellSprite)
    : map_(map), cellSprite_(cellSprite), offset_(0, 0)
{ }

void MapView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite(cellSprite_);
    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    sprite.move(offset_);

    for (int r = 0; r < map_->getRowsNo(); ++r) {
        for (int c = 0; c < map_->getColumnsNo(); ++c) {
            if (map_->isVisible(r, c))
                target.draw(sprite, states);

            sprite.move(xShift, 0);
        }
        sprite.move(-(map_->getColumnsNo() * xShift), yShift);
    }
}

void MapView::setOffset(const sf::Vector2f& offset) {
    offset_ = offset;
}

float MapView::width() const {
    const float spriteXSize = cellSprite_.getLocalBounds().width;
    return 2 * offset_.x + (map_->getColumnsNo() - 1) + map_->getColumnsNo() * spriteXSize;
}

float MapView::height() const {
    const float spriteYSize = cellSprite_.getLocalBounds().height;
    return 2 * offset_.y + (map_->getRowsNo() - 1) + map_->getRowsNo() * spriteYSize;
}

int MapView::convertXCoordsToColumnNo(int x) const {
    int column = floor((x - offset_.x) / (cellSprite_.getLocalBounds().width + 1));

    if (column < 0 || column >= map_->getColumnsNo())
        return Map::OutOfBounds;
    else
        return column;
}

int MapView::convertYCoordsToRowNo(int y) const {
    int row = floor((y - offset_.y) / (cellSprite_.getLocalBounds().height + 1));

    if (row < 0 || row >= map_->getRowsNo())
        return Map::OutOfBounds;
    else
        return row;
}
