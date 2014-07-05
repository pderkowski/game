/* Copyright 2014 <Piotr Derkowski> */

#include "Attributes.hpp"
#include "TileEnums.hpp"

using namespace tileenums;

Attributes::River::River()
    : directions_(0)
{ }

void Attributes::River::addDirection(Direction direction) {
    directions_ |= static_cast<int>(direction);
}

void Attributes::River::resetDirections() {
    directions_ = 0;
}

bool Attributes::River::hasDirection(Direction direction) const {
    return directions_ & static_cast<int>(direction);
}
