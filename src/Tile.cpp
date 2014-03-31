/* Copyright 2014 <Piotr Derkowski> */

#include "Tile.hpp"

Tile::Tile()
    : type_(Type::Empty)
{ }

Tile::Tile(Type type)
    : type_(type)
{ }

Tile::Type Tile::getType() {
    return type_;
}

void Tile::setType(Type type) {
    type_ = type;
}
