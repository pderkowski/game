/* Copyright 2014 <Piotr Derkowski> */

#include "Attributes.hpp"
#include "TileEnums.hpp"

using namespace tileenums;


namespace map {


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

bool Attributes::operator == (const Attributes& rhs) const {
    return river == rhs.river;
}

bool Attributes::River::operator == (const Attributes::River& rhs) const {
    return directions_ == rhs.directions_;
}


}  // namespace map
