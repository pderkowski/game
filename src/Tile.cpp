/* Copyright 2014 <Piotr Derkowski> */

#include "Tile.hpp"
#include "Coordinates.hpp"

Tile::Tile(const coords::RotatedPoint& coordinates)
    : coordinates(coordinates), type(Type::Empty), isVisible(true)
{ }

Tile::Tile(const coords::RotatedPoint& coordinates, Type type)
    : coordinates(coordinates), type(type), isVisible(true)
{ }

void Tile::toggleVisibility() {
    isVisible = !isVisible;
}
