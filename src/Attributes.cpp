/* Copyright 2014 <Piotr Derkowski> */

#include "Attributes.hpp"

Attributes::River::River()
    : directions_(0)
{ }

void Attributes::River::addDirection(RiverDirection direction) {
    directions_ |= static_cast<int>(direction);
}

void Attributes::River::resetDirections() {
    directions_ = 0;
}

bool Attributes::River::hasDirection(RiverDirection direction) const {
    return directions_ & direction;
}
