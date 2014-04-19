/* Copyright 2014 <Piotr Derkowski> */

#include "Tile.hpp"

Tile::Tile()
    : type_(Type::Empty), isVisible_(true)
{ }

Tile::Tile(Type type)
    : type_(type), isVisible_(true)
{ }

Tile::Type Tile::getType() {
    return type_;
}

void Tile::setType(Type type) {
    type_ = type;
}

void Tile::toggleVisibility() {
    isVisible_ = !isVisible_;
}

bool Tile::isVisible() const {
    return isVisible_;
}
