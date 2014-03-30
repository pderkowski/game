/* Copyright 2014 <Piotr Derkowski> */

#include <SFML/Graphics.hpp>
#include "BoardView.hpp"

BoardView::BoardView(int rows, int columns, const sf::Sprite& cellSprite)
    : rows_(rows), columns_(columns), cellSprite_(cellSprite), offset_(0, 0)
{ }

void BoardView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite(cellSprite_);
    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    sprite.move(offset_);

    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < columns_; ++c) {
            target.draw(sprite, states);
            sprite.move(xShift, 0);
        }
        sprite.move(-(columns_ * xShift), yShift);
    }
}

void BoardView::setOffset(const sf::Vector2f& offset) {
    offset_ = offset;
}


float BoardView::width() const {
    const float spriteXSize = cellSprite_.getLocalBounds().width;
    return 2 * offset_.x + (columns_ - 1) + columns_ * spriteXSize;
}

float BoardView::height() const {
    const float spriteYSize = cellSprite_.getLocalBounds().height;
    return 2 * offset_.y + (rows_ - 1) + rows_ * spriteYSize;
}
