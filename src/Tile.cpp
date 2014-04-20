/* Copyright 2014 <Piotr Derkowski> */

#include "Tile.hpp"

Tile::Tile(int row, int column)
    : row(row), column(column), type(Type::Empty), isVisible(true)
{ }

Tile::Tile(int row, int column, Type type)
    : row(row), column(column), type(type), isVisible(true)
{ }

void Tile::toggleVisibility() {
    isVisible = !isVisible;
}
