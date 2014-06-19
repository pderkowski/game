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

bool operator == (const Tile& lhs, const Tile& rhs) {
    return lhs.coords == rhs.coords;
}

bool operator != (const Tile& lhs, const Tile& rhs) {
    return lhs.coords != rhs.coords;
}
