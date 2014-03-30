/* Copyright 2014 <Piotr Derkowski> */

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

Grid::Grid(int rows, int columns, const sf::Sprite& cellSprite)
    : rows(rows), columns(columns), cellSprite(cellSprite)
{ }

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite sprite(cellSprite);
    const float xShift = sprite.getLocalBounds().width + 1;
    const float yShift = sprite.getLocalBounds().height + 1;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            target.draw(sprite, states);
            sprite.move(xShift, 0);
        }
        sprite.move(-(columns * xShift), yShift);
    }
}
