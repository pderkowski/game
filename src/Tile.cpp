/* Copyright 2014 <Piotr Derkowski> */

#include "Tile.hpp"
#include "Coordinates.hpp"

Tile::Tile(const IntRotPoint& coordinates)
    : coordinates(coordinates), type(Type::Empty), isVisible(true)
{ }

Tile::Tile(const IntRotPoint& coordinates, Type type)
    : coordinates(coordinates), type(type), isVisible(true)
{ }

void Tile::toggleVisibility() {
    isVisible = !isVisible;
}
