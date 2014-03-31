/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include "SFML/Graphics.hpp"
#include "BoardView.hpp"

BoardView::BoardView(std::shared_ptr<Board> board, const sf::Sprite& cellSprite)
    : board_(board), cellSprite_(cellSprite), offset_(0, 0)
{ }

void BoardView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite(cellSprite_);
    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    sprite.move(offset_);

    for (int r = 0; r < board_->getRowsNo(); ++r) {
        for (int c = 0; c < board_->getColumnsNo(); ++c) {
            if (board_->isVisible(r, c))
                target.draw(sprite, states);

            sprite.move(xShift, 0);
        }
        sprite.move(-(board_->getColumnsNo() * xShift), yShift);
    }
}

void BoardView::setOffset(const sf::Vector2f& offset) {
    offset_ = offset;
}

float BoardView::width() const {
    const float spriteXSize = cellSprite_.getLocalBounds().width;
    return 2 * offset_.x + (board_->getColumnsNo() - 1) + board_->getColumnsNo() * spriteXSize;
}

float BoardView::height() const {
    const float spriteYSize = cellSprite_.getLocalBounds().height;
    return 2 * offset_.y + (board_->getRowsNo() - 1) + board_->getRowsNo() * spriteYSize;
}

int BoardView::convertXCoordsToColumnNo(int x) const {
    int column = floor((x - offset_.x) / (cellSprite_.getLocalBounds().width + 1));

    if (column < 0 || column >= board_->getColumnsNo())
        return Board::OutOfBounds;
    else
        return column;
}

int BoardView::convertYCoordsToRowNo(int y) const {
    int row = floor((y - offset_.y) / (cellSprite_.getLocalBounds().height + 1));

    if (row < 0 || row >= board_->getRowsNo())
        return Board::OutOfBounds;
    else
        return row;
}
