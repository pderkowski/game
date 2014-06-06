/* Copyright 2014 <Piotr Derkowski> */

#include "Tile.hpp"
#include "Coordinates.hpp"

Tile::Tile(const IntRotPoint& coords)
    : coords(coords), type(Type::Empty), isVisible(true)
{ }

Tile::Tile(const IntRotPoint& coords, Type type)
    : coords(coords), type(type), isVisible(true)
{ }

void Tile::toggleVisibility() {
    isVisible = !isVisible;
}
